/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2024 OpenStickCommunity (gp2040-ce.info)
 */

#ifndef PICO_BOARD_CONFIG_H_
#define PICO_BOARD_CONFIG_H_

#include "enums.pb.h"
#include "class/hid/hid.h"

#define BOARD_CONFIG_LABEL "17XL"

// -----------------------------------------------------------------------------
// Main GPIO pin mapping
// -----------------------------------------------------------------------------

// Directions / auxiliary direction buttons
#define GPIO_PIN_00 GpioAction::BUTTON_PRESS_UP       // Up
#define GPIO_PIN_01 GpioAction::BUTTON_PRESS_L3       // L3
#define GPIO_PIN_02 GpioAction::BUTTON_PRESS_LEFT     // Left
#define GPIO_PIN_03 GpioAction::BUTTON_PRESS_DOWN     // Down
#define GPIO_PIN_04 GpioAction::BUTTON_PRESS_RIGHT    // Right
#define GPIO_PIN_05 GpioAction::BUTTON_PRESS_UP       // Up
#define GPIO_PIN_06 GpioAction::BUTTON_PRESS_L3       // L3
#define GPIO_PIN_07 GpioAction::BUTTON_PRESS_R3       // R3
#define GPIO_PIN_08 GpioAction::BUTTON_PRESS_R3       // R3
#define GPIO_PIN_09 GpioAction::BUTTON_PRESS_B1       // K1
#define GPIO_PIN_10 GpioAction::BUTTON_PRESS_B2       // K2
#define GPIO_PIN_11 GpioAction::BUTTON_PRESS_R2       // K3
#define GPIO_PIN_12 GpioAction::BUTTON_PRESS_L2       // K4
#define GPIO_PIN_13 GpioAction::BUTTON_PRESS_B3       // P1
#define GPIO_PIN_14 GpioAction::BUTTON_PRESS_B4       // P2
#define GPIO_PIN_15 GpioAction::BUTTON_PRESS_R1       // P3
#define GPIO_PIN_16 GpioAction::BUTTON_PRESS_L1       // P4
#define GPIO_PIN_17 GpioAction::BUTTON_PRESS_R3       // R3
#define GPIO_PIN_18 GpioAction::BUTTON_PRESS_S1       // Select
#define GPIO_PIN_19 GpioAction::BUTTON_PRESS_S2       // Start
#define GPIO_PIN_22 GpioAction::BUTTON_PRESS_A1       // Home / Guide / PS

// GPIOs reserved for peripherals
#define GPIO_PIN_20 GpioAction::ASSIGNED_TO_ADDON     // OLED SDA
#define GPIO_PIN_21 GpioAction::ASSIGNED_TO_ADDON     // OLED SCL
#define GPIO_PIN_26 GpioAction::ASSIGNED_TO_ADDON     // USB Host D-
#define GPIO_PIN_27 GpioAction::ASSIGNED_TO_ADDON     // USB Host D+

// -----------------------------------------------------------------------------
// Keyboard mapping
// Uses the standard GP2040-CE keyboard defaults.
// -----------------------------------------------------------------------------

#define KEY_DPAD_UP     HID_KEY_ARROW_UP
#define KEY_DPAD_DOWN   HID_KEY_ARROW_DOWN
#define KEY_DPAD_RIGHT  HID_KEY_ARROW_RIGHT
#define KEY_DPAD_LEFT   HID_KEY_ARROW_LEFT

#define KEY_BUTTON_B1   HID_KEY_SHIFT_LEFT
#define KEY_BUTTON_B2   HID_KEY_Z
#define KEY_BUTTON_R2   HID_KEY_X
#define KEY_BUTTON_L2   HID_KEY_V

#define KEY_BUTTON_B3   HID_KEY_CONTROL_LEFT
#define KEY_BUTTON_B4   HID_KEY_ALT_LEFT
#define KEY_BUTTON_R1   HID_KEY_SPACE
#define KEY_BUTTON_L1   HID_KEY_C

#define KEY_BUTTON_S1   HID_KEY_5
#define KEY_BUTTON_S2   HID_KEY_1
#define KEY_BUTTON_L3   HID_KEY_EQUAL
#define KEY_BUTTON_R3   HID_KEY_MINUS
#define KEY_BUTTON_A1   HID_KEY_9
#define KEY_BUTTON_A2   HID_KEY_F2
#define KEY_BUTTON_FN   -1

// -----------------------------------------------------------------------------
// OLED / I2C
//
// GP20 = SDA and GP21 = SCL form a valid I2C0 pair on RP2040.
// -----------------------------------------------------------------------------

#define HAS_I2C_DISPLAY 1

#define I2C0_ENABLED 1
#define I2C0_PIN_SDA 20
#define I2C0_PIN_SCL 21

#define DISPLAY_I2C_BLOCK i2c0

// -----------------------------------------------------------------------------
// USB Host / Passthrough
//
// Physical wiring:
//   D- = GPIO26
//   D+ = GPIO27
//
// USB_PERIPHERAL_PIN_ORDER = 1 selects the D-/D+ GPIO ordering, because
// GPIO26 immediately precedes GPIO27.
// -----------------------------------------------------------------------------

#define USB_PERIPHERAL_ENABLED 1
#define USB_PERIPHERAL_PIN_DPLUS 27
#define USB_PERIPHERAL_PIN_ORDER 1
#define SPLASH_MODE SPLASH_MODE_STATIC
#define SPLASH_DURATION 3000
#define DEFAULT_INPUT_MODE INPUT_MODE_XINPUT
#define DEFAULT_INPUT_MODE_R1 INPUT_MODE_XBONE
#define DEFAULT_INPUT_MODE_B4 INPUT_MODE_PS5
#define DEFAULT_PS5AUTHENTICATION_TYPE INPUT_MODE_AUTH_TYPE_USB

// -----------------------------------------------------------------------------
// OLED button layout
// -----------------------------------------------------------------------------

#define BUTTON_LAYOUT BUTTON_LAYOUT_BOARD_DEFINED_A
#define BUTTON_LAYOUT_RIGHT BUTTON_LAYOUT_BOARD_DEFINED_B

#define DEFAULT_BOARD_LAYOUT_A_NAME "Custom Arcade Left"
#define DEFAULT_BOARD_LAYOUT_A {\
    {GP_ELEMENT_PIN_BUTTON, {36, 20, 4, 4, 1, 1, 0,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {13, 33, 4, 4, 1, 1, 1,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {24, 28, 4, 4, 1, 1, 2,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {34, 29, 4, 4, 1, 1, 3,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {43, 33, 4, 4, 1, 1, 4,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {51, 49, 5, 5, 1, 1, 5,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {40, 46, 4, 4, 1, 1, 6,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {94, 14, 2, 2, 1, 1, 19, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {99, 14, 2, 2, 1, 1, 18, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {104,14, 2, 2, 1, 1, 22, GP_SHAPE_ELLIPSE}},\
}

#define DEFAULT_BOARD_LAYOUT_B_NAME "Custom Arcade Right"
#define DEFAULT_BOARD_LAYOUT_B {\
    {GP_ELEMENT_PIN_BUTTON, {86, 20, 4, 4, 1, 1, 17, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {84, 29, 4, 4, 1, 1, 13, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {85, 38, 4, 4, 1, 1, 9,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {94, 25, 4, 4, 1, 1, 14, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {94, 34, 4, 4, 1, 1, 10, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {92, 46, 4, 4, 1, 1, 8,  GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {104,26, 4, 4, 1, 1, 15, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {105,35, 4, 4, 1, 1, 11, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {114,27, 4, 4, 1, 1, 16, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {115,36, 4, 4, 1, 1, 12, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {81, 49, 5, 5, 1, 1, 7,  GP_SHAPE_ELLIPSE}},\
}

#endif