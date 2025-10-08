/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2024 OpenStickCommunity (gp2040-ce.info)
 */

#ifndef PICO_BOARD_CONFIG_H_
#define PICO_BOARD_CONFIG_H_

#include "enums.pb.h"
#include "class/hid/hid.h"

#define BOARD_CONFIG_LABEL "17XL"

// Main pin mapping Configuration
//                                                  // Flatbox Rev5 SW# | GP2040 | Xinput | Switch  | PS3/4/5  | Dinput | Arcade |
#define GPIO_PIN_05 GpioAction::BUTTON_PRESS_UP     // UP     | UP     | UP      | UP       | UP     | UP     |
#define GPIO_PIN_03 GpioAction::BUTTON_PRESS_DOWN   // DOWN   | DOWN   | DOWN    | DOWN     | DOWN   | DOWN   |
#define GPIO_PIN_04 GpioAction::BUTTON_PRESS_RIGHT  // RIGHT  | RIGHT  | RIGHT   | RIGHT    | RIGHT  | RIGHT  |
#define GPIO_PIN_02 GpioAction::BUTTON_PRESS_LEFT   // LEFT   | LEFT   | LEFT    | LEFT     | LEFT   | LEFT   |
#define GPIO_PIN_14 GpioAction::BUTTON_PRESS_B1     // B1     | A      | B       | Cross    | 2      | K1     |
#define GPIO_PIN_13 GpioAction::BUTTON_PRESS_B2     // B2     | B      | A       | Circle   | 3      | K2     |
#define GPIO_PIN_12 GpioAction::BUTTON_PRESS_R2     // R2     | RT     | ZR      | R2       | 8      | K3     |
#define GPIO_PIN_11 GpioAction::BUTTON_PRESS_L2     // L2     | LT     | ZL      | L2       | 7      | K4     |
#define GPIO_PIN_16 GpioAction::BUTTON_PRESS_B3     // B3     | X      | Y       | Square   | 1      | P1     |
#define GPIO_PIN_17 GpioAction::BUTTON_PRESS_B4     // B4     | Y      | X       | Triangle | 4      | P2     |
#define GPIO_PIN_18 GpioAction::BUTTON_PRESS_R1     // R1     | RB     | R       | R1       | 6      | P3     |
#define GPIO_PIN_19 GpioAction::BUTTON_PRESS_L1     // L1     | LB     | L       | L1       | 5      | P4     |
#define GPIO_PIN_07 GpioAction::BUTTON_PRESS_S1     // S1     | Back   | Minus   | Select   | 9      | Coin   |
#define GPIO_PIN_10 GpioAction::BUTTON_PRESS_S2     // S2     | Start  | Plus    | Start    | 10     | Start  |
#define GPIO_PIN_08 GpioAction::BUTTON_PRESS_A1     // A1     | Guide  | Home    | PS       | 13     | ~      |
#define GPIO_PIN_28 GpioAction::BUTTON_PRESS_A2     // A2     | ~      | Capture | ~        | 14     | ~      |
#define GPIO_PIN_01 GpioAction::BUTTON_PRESS_L3     // L3     | LS     | LS      | L3       | 11     | LS     |
#define GPIO_PIN_15 GpioAction::BUTTON_PRESS_R3     // R3     | RS     | RS      | R3       | 12     | RS     |
#define GPIO_PIN_00 GpioAction::BUTTON_PRESS_E1     // Extra 1
#define GPIO_PIN_06 GpioAction::BUTTON_PRESS_E2     // Extra 2
#define GPIO_PIN_22 GpioAction::BUTTON_PRESS_E3     // Extra 3

// Keyboard Mapping Configuration
//                                            // GP2040 | Xinput | Switch  | PS3/4/5  | Dinput | Arcade |
#define KEY_DPAD_UP     HID_KEY_ARROW_UP      // UP     | UP     | UP      | UP       | UP     | UP     |
#define KEY_DPAD_DOWN   HID_KEY_ARROW_DOWN    // DOWN   | DOWN   | DOWN    | DOWN     | DOWN   | DOWN   |
#define KEY_DPAD_RIGHT  HID_KEY_ARROW_RIGHT   // RIGHT  | RIGHT  | RIGHT   | RIGHT    | RIGHT  | RIGHT  |
#define KEY_DPAD_LEFT   HID_KEY_ARROW_LEFT    // LEFT   | LEFT   | LEFT    | LEFT     | LEFT   | LEFT   |
#define KEY_BUTTON_B1   HID_KEY_SHIFT_LEFT    // B1     | A      | B       | Cross    | 2      | K1     |
#define KEY_BUTTON_B2   HID_KEY_Z             // B2     | B      | A       | Circle   | 3      | K2     |
#define KEY_BUTTON_R2   HID_KEY_X             // R2     | RT     | ZR      | R2       | 8      | K3     |
#define KEY_BUTTON_L2   HID_KEY_V             // L2     | LT     | ZL      | L2       | 7      | K4     |
#define KEY_BUTTON_B3   HID_KEY_CONTROL_LEFT  // B3     | X      | Y       | Square   | 1      | P1     |
#define KEY_BUTTON_B4   HID_KEY_ALT_LEFT      // B4     | Y      | X       | Triangle | 4      | P2     |
#define KEY_BUTTON_R1   HID_KEY_SPACE         // R1     | RB     | R       | R1       | 6      | P3     |
#define KEY_BUTTON_L1   HID_KEY_C             // L1     | LB     | L       | L1       | 5      | P4     |
#define KEY_BUTTON_S1   HID_KEY_5             // S1     | Back   | Minus   | Select   | 9      | Coin   |
#define KEY_BUTTON_S2   HID_KEY_1             // S2     | Start  | Plus    | Start    | 10     | Start  |
#define KEY_BUTTON_L3   HID_KEY_EQUAL         // L3     | LS     | LS      | L3       | 11     | LS     |
#define KEY_BUTTON_R3   HID_KEY_MINUS         // R3     | RS     | RS      | R3       | 12     | RS     |
#define KEY_BUTTON_A1   HID_KEY_9             // A1     | Guide  | Home    | PS       | 13     | ~      |
#define KEY_BUTTON_A2   HID_KEY_F2            // A2     | ~      | Capture | ~        | 14     | ~      |
#define KEY_BUTTON_FN   -1                    // Hotkey Function                                        |

#define DEFAULT_INPUT_MODE INPUT_MODE_XINPUT
#define DEFAULT_INPUT_MODE_R1 INPUT_MODE_XBONE
#define DEFAULT_INPUT_MODE_B4 INPUT_MODE_PS5
#define DEFAULT_PS5AUTHENTICATION_TYPE INPUT_MODE_AUTH_TYPE_USB

#define USB_PERIPHERAL_ENABLED 1
#define USB_PERIPHERAL_PIN_DPLUS 27

#define GPIO_PIN_27 GpioAction::ASSIGNED_TO_ADDON
#define GPIO_PIN_26 GpioAction::ASSIGNED_TO_ADDON
#define GPIO_PIN_21 GpioAction::ASSIGNED_TO_ADDON
#define GPIO_PIN_20 GpioAction::ASSIGNED_TO_ADDON

#define HAS_I2C_DISPLAY 1
#define I2C0_ENABLED 1
#define I2C0_PIN_SDA 20
#define I2C0_PIN_SCL 21
#define DISPLAY_I2C_BLOCK i2c0
#define DISPLAY_FLIP 0

#define BUTTON_LAYOUT BUTTON_LAYOUT_BOARD_DEFINED_A
#define BUTTON_LAYOUT_RIGHT BUTTON_LAYOUT_BOARD_DEFINED_B
#define SPLASH_MODE SPLASH_MODE_STATIC
#define SPLASH_DURATION 3000

#define DEFAULT_BOARD_LAYOUT_A {\
    {GP_ELEMENT_PIN_BUTTON, {45, 17, 4, 4, 1, 1, 0, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {32, 27, 4, 4, 1, 1, 2, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {42, 27, 4, 4, 1, 1, 3, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {50, 32, 4, 4, 1, 1, 4, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {62, 17, 4, 4, 1, 1, 22, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {55, 50, 5, 5, 1, 1, 5, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {47, 42, 4, 4, 1, 1, 1, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {84, 15, 2, 2, 1, 1, 10, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {91, 15, 2, 2, 1, 1, 7, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {98, 15, 2, 2, 1, 1, 8, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {105, 15, 2, 2, 1, 1, 28, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {22, 29, 4, 4, 1, 1, 6, GP_SHAPE_ELLIPSE}},\
}

#define DEFAULT_BOARD_LAYOUT_B {\
    {GP_ELEMENT_PIN_BUTTON, {59, 27, 4, 4, 1, 1, 16, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {69, 25, 4, 4, 1, 1, 17, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {79, 25, 4, 4, 1, 1, 18, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {89, 27, 4, 4, 1, 1, 19, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {59, 37, 4, 4, 1, 1, 14, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {69, 35, 4, 4, 1, 1, 13, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {79, 35, 4, 4, 1, 1, 12, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {89, 37, 4, 4, 1, 1, 11, GP_SHAPE_ELLIPSE}},\
    {GP_ELEMENT_PIN_BUTTON, {66, 45, 4, 4, 1, 1, 15, GP_SHAPE_ELLIPSE}},\
}

#endif