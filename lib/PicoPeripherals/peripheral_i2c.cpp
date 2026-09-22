#include <cstdio>
#include <hardware/clocks.h>
#include "peripheral_i2c.h"

PeripheralI2C::PeripheralI2C() {
#ifdef PICO_DEFAULT_I2C_INSTANCE

#if PICO_SDK_VERSION_MAJOR >= 2
    _I2C = PICO_DEFAULT_I2C_INSTANCE();
#else
    _I2C = PICO_DEFAULT_I2C_INSTANCE;
#endif

    _SDA = PICO_DEFAULT_I2C_SDA_PIN;
    _SCL = PICO_DEFAULT_I2C_SCL_PIN;
    _Speed = DEFAULT_SPEED;
#endif
}

void PeripheralI2C::setConfig(uint8_t block, int8_t sda, int8_t scl, uint32_t speed) {
    if (_backend == I2CBackend::PIO) {
        deinitPIO();
        _backend = I2CBackend::Hardware;
    }

    if ((block < NUM_I2CS) && (sda > -1) && (scl > -1)) {
        _I2C = _hardwareBlocks[block];
        _SDA = sda;
        _SCL = scl;
        _Speed = speed;
        configured = true;
        setup();
    } else {
        // currently not supported
    }
}

bool PeripheralI2C::setConfigPIO(int8_t sda, int8_t scl, uint32_t speed) {
    if ((sda < 0) || (scl < 0)) {
        configured = false;
        return false;
    }

    // Idempotent: reuse the existing allocation if nothing changed.
    if (_backend == I2CBackend::PIO && configured && _pioProgramLoaded &&
        _SDA == (uint8_t)sda && _SCL == (uint8_t)scl && (uint32_t)_Speed == speed) {
        return true;
    }

    // Cleanly tear down any previous PIO allocation before re-initialising.
    deinitPIO();

    _backend = I2CBackend::PIO;
    _SDA = sda;
    _SCL = scl;
    _Speed = speed;

    // Allocate a PIO state machine and instruction space without hard-coding
    // an instance/SM.  GP2040-CE already uses:
    //   - PIO0: Pico-PIO-USB host (claims SMs 0-2 and loads its programs
    //     *after* PeripheralManager::initI2C() runs, hard-asserting if there
    //     is no room), and
    //   - PIO1: NeoPico WS2812 RGB (uses SM0 directly, without SDK claiming).
    // Prefer PIO1 (which only ever hosts the small WS2812 program) so we can
    // never starve the USB host's program space on PIO0, then fall back to
    // PIO0.  Verify program space and claim an unused SM via the SDK rather
    // than assuming a specific SM is free.
    const PIO candidates[NUM_PIOS] = { pio1, pio0 };
    for (uint i = 0; i < NUM_PIOS; i++) {
        PIO pio = candidates[i];
        if (!pio_can_add_program(pio, &i2c_program))
            continue;

        // Prefer higher SM numbers: SM0 on PIO1 belongs to WS2812 (unclaimed
        // via SDK), and SMs 0-2 on PIO0 belong to the USB host (claimed after
        // peripheral init).
        for (int sm = NUM_PIO_STATE_MACHINES - 1; sm >= 0; sm--) {
            if (pio_sm_is_claimed(pio, sm))
                continue;

            pio_sm_claim(pio, sm);
            _pio = pio;
            _pioSm = sm;
            _pioOffset = pio_add_program(pio, &i2c_program);
            _pioProgramLoaded = true;
            _pioBusHeld = false;

            setupPIO();

            configured = true;
            return true;
        }
    }

    // No usable PIO program space / state machine available.
    configured = false;
    return false;
}

void PeripheralI2C::setup() {
    if ((_SDA + 2 * i2c_hw_index(_I2C))%4 != 0) return;
    if ((_SCL + 3 + 2 * i2c_hw_index(_I2C))%4 != 0) return;

    i2c_init(_I2C, _Speed);
    gpio_set_function(_SDA, GPIO_FUNC_I2C);
    gpio_set_function(_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(_SDA);
    gpio_pull_up(_SCL);

    // reset the bus before using it
    clear();
}

void PeripheralI2C::setupPIO() {
    PIO pio = _pio;
    uint sm = _pioSm;

    pio_sm_config c = i2c_program_get_default_config(_pioOffset);

    // IO mapping
    sm_config_set_out_pins(&c, _SDA, 1);
    sm_config_set_set_pins(&c, _SDA, 1);
    sm_config_set_in_pins(&c, _SDA);
    sm_config_set_sideset_pins(&c, _SCL);
    sm_config_set_jmp_pin(&c, _SDA);

    sm_config_set_out_shift(&c, false, true, 16);
    sm_config_set_in_shift(&c, false, true, 8);

    // One SCL cycle is 32 state-machine cycles: scale the system clock to the
    // requested bus frequency (clamped to the fastest achievable rate).
    float div = (float)clock_get_hz(clk_sys) / (32.0f * (float)_Speed);
    if (div < 1.0f)
        div = 1.0f;
    sm_config_set_clkdiv(&c, div);

    // Try to avoid glitching the bus while connecting the IOs.  The OE outputs
    // are inverted so that PIO "drive 1" means high-impedance (pull-up raises
    // the line) and PIO "drive 0" means actively low - i.e. open-drain.
    gpio_pull_up(_SCL);
    gpio_pull_up(_SDA);
    uint32_t both_pins = (1u << _SDA) | (1u << _SCL);
    pio_sm_set_pins_with_mask(pio, sm, both_pins, both_pins);
    pio_sm_set_pindirs_with_mask(pio, sm, both_pins, both_pins);
    pio_gpio_init(pio, _SDA);
    gpio_set_oeover(_SDA, GPIO_OVERRIDE_INVERT);
    pio_gpio_init(pio, _SCL);
    gpio_set_oeover(_SCL, GPIO_OVERRIDE_INVERT);
    pio_sm_set_pins_with_mask(pio, sm, 0, both_pins);

    // Clear IRQ flag before starting, and make sure flag doesn't actually
    // assert a system-level interrupt (we're using it as a status flag).
    pio_set_irq0_source_enabled(pio, (enum pio_interrupt_source) ((uint) pis_interrupt0 + sm), false);
    pio_set_irq1_source_enabled(pio, (enum pio_interrupt_source) ((uint) pis_interrupt0 + sm), false);
    pio_interrupt_clear(pio, sm);

    // Configure and start SM.
    pio_sm_init(pio, sm, _pioOffset + i2c_offset_entry_point, &c);
    pio_sm_set_enabled(pio, sm, true);
}

void PeripheralI2C::deinitPIO() {
    if (_pioProgramLoaded && _pio != nullptr) {
        pio_sm_set_enabled(_pio, _pioSm, false);
        pio_remove_program(_pio, &i2c_program, _pioOffset);
        pio_sm_unclaim(_pio, _pioSm);
        _pioProgramLoaded = false;
    }
    _pioBusHeld = false;
}

int16_t PeripheralI2C::read(uint8_t address, uint8_t *data, uint16_t len, bool isBlock) {
    if ((_exclusiveAddress > -1) && (_exclusiveAddress != address)) return -1;

    int16_t result;
    if (_backend == I2CBackend::PIO) {
        result = pio_i2c_read_blocking(_pio, _pioSm, address, data, len, isBlock, _pioBusHeld);
        _pioBusHeld = (result >= 0) && isBlock;
    } else {
        result = i2c_read_blocking(_I2C, address, data, len, isBlock);
    }
#ifdef DEBUG_PERIPHERALI2C
    printf("PeripheralI2C::write %d:%d (blocking? %d)\n", address, len, isBlock);
    for (int i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\nResult: %d\n", result);
    printf("-----\n");
#endif    
    return result;
}

int16_t PeripheralI2C::readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len) {
    if ((_exclusiveAddress > -1) && (_exclusiveAddress != address)) return -1;

    int16_t registerCheck;
    if (_backend == I2CBackend::PIO) {
        // write register pointer without STOP, then read back with a repeated
        // START - identical to the hardware I2C path below.
        registerCheck = pio_i2c_write_blocking(_pio, _pioSm, address, &reg, 1, true, _pioBusHeld);
        _pioBusHeld = (registerCheck >= 0);
        if (registerCheck >= 0) {
            registerCheck = pio_i2c_read_blocking(_pio, _pioSm, address, data, len, false, _pioBusHeld);
            _pioBusHeld = false;
        }
    } else {
        registerCheck = i2c_write_blocking(_I2C, address, &reg, 1, true);
        if (registerCheck >= 0) {
            registerCheck = i2c_read_blocking(_I2C, address, data, len, false);
        }
    }
    return (registerCheck >= 0);
}

int16_t PeripheralI2C::write(uint8_t address, uint8_t *data, uint16_t len, bool isBlock) {
    if ((_exclusiveAddress > -1) && (_exclusiveAddress != address)) return -1;

#ifdef DEBUG_PERIPHERALI2C
    printf("PeripheralI2C::write %d:%d (blocking? %d)\n", address, len, isBlock);
    for (int i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
#endif
    int16_t result;
    if (_backend == I2CBackend::PIO) {
        result = pio_i2c_write_blocking(_pio, _pioSm, address, data, len, isBlock, _pioBusHeld);
        _pioBusHeld = (result >= 0) && isBlock;
    } else {
        result = i2c_write_blocking(_I2C, address, data, len, isBlock);
    }
#ifdef DEBUG_PERIPHERALI2C
    printf("\nResult: %d\n", result);
    printf("-----\n");
#endif
    return result;
}

uint8_t PeripheralI2C::test(uint8_t address) {
    uint8_t data;
    int16_t ret;
    if (_backend == I2CBackend::PIO) {
        ret = pio_i2c_read_blocking(_pio, _pioSm, address, &data, 1, false, _pioBusHeld);
        _pioBusHeld = false;
    } else {
        ret = i2c_read_blocking(_I2C, address, &data, 1, false);
    }
    return (ret >= 0);
}

void PeripheralI2C::clear() {
    // reset the bus
    test(0xFF);
}

std::map<uint8_t,bool> PeripheralI2C::scan() {
    std::map<uint8_t,bool> result;

    for (uint8_t addr = 0; addr < (1 << 7); ++addr) {
        int8_t ret;
        uint8_t rxdata;
        if (_backend == I2CBackend::PIO) {
            ret = pio_i2c_read_blocking(_pio, _pioSm, addr, &rxdata, 1, false, _pioBusHeld);
            _pioBusHeld = false;
        } else {
            ret = i2c_read_blocking(_I2C, addr, &rxdata, 1, false);
        }

        if (ret >= 0) {
            result.insert({addr,(ret >= 0)});
        }
    }

#ifdef DEBUG_PERIPHERALI2C
    printf("%d\n", result.size());
#endif

    return result;
}
