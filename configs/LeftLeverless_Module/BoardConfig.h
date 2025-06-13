/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2024 OpenStickCommunity (gp2040-ce.info)
 */

#ifndef PICO_BOARD_CONFIG_H_
#define PICO_BOARD_CONFIG_H_

#include "enums.pb.h"
#include "class/hid/hid.h"

#define BOARD_CONFIG_LABEL "Left Leverless Module"

// Main pin mapping Configuration
//                                                  // Flatbox Rev5 SW# | GP2040 | Xinput | Switch  | PS3/4/5  | Dinput | Arcade |
#define GPIO_PIN_14 GpioAction::BUTTON_PRESS_UP     // UP     | UP     | UP      | UP       | UP     | UP     |
#define GPIO_PIN_26 GpioAction::BUTTON_PRESS_DOWN   // DOWN   | DOWN   | DOWN    | DOWN     | DOWN   | DOWN   |
#define GPIO_PIN_15 GpioAction::BUTTON_PRESS_RIGHT  // RIGHT  | RIGHT  | RIGHT   | RIGHT    | RIGHT  | RIGHT  |
#define GPIO_PIN_27 GpioAction::BUTTON_PRESS_LEFT   // LEFT   | LEFT   | LEFT    | LEFT     | LEFT   | LEFT   |


// Setting GPIO pins to assigned by add-on
//
#define GPIO_PIN_06 GpioAction::ASSIGNED_TO_ADDON
#define GPIO_PIN_07 GpioAction::ASSIGNED_TO_ADDON

// Keyboard Mapping Configuration
//                                            // GP2040 | Xinput | Switch  | PS3/4/5  | Dinput | Arcade |
#define KEY_DPAD_UP     HID_KEY_ARROW_UP      // UP     | UP     | UP      | UP       | UP     | UP     |
#define KEY_DPAD_DOWN   HID_KEY_ARROW_DOWN    // DOWN   | DOWN   | DOWN    | DOWN     | DOWN   | DOWN   |
#define KEY_DPAD_RIGHT  HID_KEY_ARROW_RIGHT   // RIGHT  | RIGHT  | RIGHT   | RIGHT    | RIGHT  | RIGHT  |
#define KEY_DPAD_LEFT   HID_KEY_ARROW_LEFT    // LEFT   | LEFT   | LEFT    | LEFT     | LEFT   | LEFT   |

#define KEY_BUTTON_B1   -1    // B1     | A      | B       | Cross    | 2      | K1     |
#define KEY_BUTTON_B2   -1             // B2     | B      | A       | Circle   | 3      | K2     |
#define KEY_BUTTON_R2   -1             // R2     | RT     | ZR      | R2       | 8      | K3     |
#define KEY_BUTTON_L2   -1             // L2     | LT     | ZL      | L2       | 7      | K4     |
#define KEY_BUTTON_B3   -1  // B3     | X      | Y       | Square   | 1      | P1     |
#define KEY_BUTTON_B4   -1     // B4     | Y      | X       | Triangle | 4      | P2     |
#define KEY_BUTTON_R1   -1        // R1     | RB     | R       | R1       | 6      | P3     |
#define KEY_BUTTON_L1   -1            // L1     | LB     | L       | L1       | 5      | P4     |
#define KEY_BUTTON_S1   -1            // S1     | Back   | Minus   | Select   | 9      | Coin   |
#define KEY_BUTTON_S2   -1             // S2     | Start  | Plus    | Start    | 10     | Start  |
#define KEY_BUTTON_L3   -1         // L3     | LS     | LS      | L3       | 11     | LS     |
#define KEY_BUTTON_R3   -1        // R3     | RS     | RS      | R3       | 12     | RS     |
#define KEY_BUTTON_A1   -1             // A1     | Guide  | Home    | PS       | 13     | ~      |
#define KEY_BUTTON_A2   -1            // A2     | ~      | Capture | ~        | 14     | ~      |
#define KEY_BUTTON_FN   -1                    // Hotkey Function                                        |

#define USB_PERIPHERAL_ENABLED 1
#define USB_PERIPHERAL_PIN_DPLUS 6

#define DEFAULT_INPUT_MODE INPUT_MODE_PS5
#define DEFAULT_INPUT_MODE_R1 INPUT_MODE_XBONE
#define DEFAULT_INPUT_MODE_B4 INPUT_MODE_PS5
#define DEFAULT_PS5AUTHENTICATION_TYPE INPUT_MODE_AUTH_TYPE_USB

#endif