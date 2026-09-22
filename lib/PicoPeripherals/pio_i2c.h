/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * PIO I2C backend for GP2040-CE.
 *
 * This is a derivative of the Raspberry Pi Pico SDK / pico-examples PIO I2C
 * implementation (pico-examples/pio/i2c/pio_i2c.{c,h}).  Adaptations:
 *
 *  - Transaction-level functions accept a `nostop` flag and a `repstart`
 *    flag so that a write-then-read register access can be performed as a
 *    single repeated-START transaction, matching the Pico SDK hardware I2C
 *    `nostop` semantics used by PeripheralI2C::readRegister().
 *  - Transaction-level functions return the number of bytes transferred on
 *    success and a negative value on error (Pico SDK hardware I2C returns
 *    `len` / `PICO_ERROR_GENERIC`), rather than upstream's 0 / -1.
 *  - Clock stretching is not supported (see pio_i2c.pio header comment), which
 *    removes the SDA/SCL adjacency constraint.
 */
#ifndef _PIO_I2C_H
#define _PIO_I2C_H

#include "hardware/pio.h"
#include "pio_i2c.pio.h"

// ----------------------------------------------------------------------------
// Low-level functions

void pio_i2c_start(PIO pio, uint sm);
void pio_i2c_stop(PIO pio, uint sm);
void pio_i2c_repstart(PIO pio, uint sm);

bool pio_i2c_check_error(PIO pio, uint sm);
void pio_i2c_resume_after_error(PIO pio, uint sm);

// If I2C is ok, block and push data. Otherwise fall straight through.
void pio_i2c_put_or_err(PIO pio, uint sm, uint16_t data);
uint8_t pio_i2c_get(PIO pio, uint sm);

// ----------------------------------------------------------------------------
// Transaction-level functions
//
// `nostop`: leave the bus held (no STOP) after the transfer so a following
//           transaction can issue a repeated START.
// `repstart`: issue a repeated START instead of a plain START because a prior
//           `nostop` transaction already holds the bus.
// Return value: number of bytes transferred on success, negative on error.

int pio_i2c_write_blocking(PIO pio, uint sm, uint8_t addr, uint8_t *txbuf, uint len, bool nostop, bool repstart);
int pio_i2c_read_blocking(PIO pio, uint sm, uint8_t addr, uint8_t *rxbuf, uint len, bool nostop, bool repstart);

#endif
