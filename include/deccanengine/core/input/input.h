/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../config.h"
#include "input_codes.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    bool IsPressed;
    bool IsReleased;
    bool IsHeld;
} deccan_key_state_t;

typedef struct {
    bool IsDown;
    bool IsUp;
} deccan_mouse_state_t;

////////////////////////////////////////////////////////////////////////////////
// Input management
////////////////////////////////////////////////////////////////////////////////

DE_API SDL_Event *deccan_input_get_event_handler(void);
DE_API void deccan_input_init(void);
DE_API void deccan_input_update(void);

////////////////////////////////////////////////////////////////////////////////
// Keyboard functions
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_key_state_t deccan_input_get_key(int key_code);

DE_API bool deccan_input_key_pressed(int key_code);
DE_API bool deccan_input_key_released(int key_code);
DE_API bool deccan_input_key_held(int key_code);

////////////////////////////////////////////////////////////////////////////////
// Mouse functions
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_mouse_state_t deccan_input_get_mouse_button(int button_code);

DE_API bool deccan_input_button_down(int button_code);
DE_API bool deccan_input_button_up(int button_code);

DE_API vec2s deccan_input_get_mouse_pos(void);
DE_API int deccan_input_mouse_scroll_horizontal(void);
DE_API int deccan_input_mouse_scroll_vertical(void);
