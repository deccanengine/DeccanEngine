/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
// #include "../Math/Vector2.h"
#include "InputCodes.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct {
    bool IsPressed;
    bool IsReleased;
    bool IsHeld;
} KeyState;

typedef struct {
    bool IsDown;
    bool IsUp;
} MouseState;

/////////////////////////////////////////////////
// Input management
////////////////////////////////////////////////

SDL_Event *Input_GetEventHandler();
void Input_Init();
void Input_Update();

/////////////////////////////////////////////////
// Keyboard functions
////////////////////////////////////////////////

KeyState Input_GetKey(int key_code);

bool Input_KeyPressed(int key_code);
bool Input_KeyReleased(int key_code);
bool Input_KeyHeld(int key_code);

/////////////////////////////////////////////////
// Mouse functions
////////////////////////////////////////////////

MouseState Input_GetMouseButton(int button_code);

bool Input_ButtonDown(int button_code);
bool Input_ButtonUp(int button_code);

void Input_GetMousePos(vec2 pos);
int Input_MouseScrollHorizontal();
int Input_MouseScrollVertical();
