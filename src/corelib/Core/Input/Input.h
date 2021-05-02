/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
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
} DeccanKeyState;

typedef struct {
    bool IsDown;
    bool IsUp;
} DeccanMouseState;

/////////////////////////////////////////////////
// Input management
////////////////////////////////////////////////

DE_API SDL_Event *DE_InputGetEventHandler(void);
DE_API void DE_InputInit(void);
DE_API void DE_InputUpdate(void);

/////////////////////////////////////////////////
// Keyboard functions
////////////////////////////////////////////////

DE_API DeccanKeyState DE_InputGetKey(int key_code);

DE_API bool DE_InputKeyPressed(int key_code);
DE_API bool DE_InputKeyReleased(int key_code);
DE_API bool DE_InputKeyHeld(int key_code);

/////////////////////////////////////////////////
// Mouse functions
////////////////////////////////////////////////

DE_API DeccanMouseState DE_InputGetMouseButton(int button_code);

DE_API bool DE_InputButtonDown(int button_code);
DE_API bool DE_InputButtonUp(int button_code);

DE_API void DE_InputGetMousePos(vec2 pos);
DE_API int DE_InputMouseScrollHorizontal(void);
DE_API int DE_InputMouseScrollVertical(void);
