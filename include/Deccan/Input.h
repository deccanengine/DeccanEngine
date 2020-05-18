/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <Deccan/Config.h>

/* Key Codes */
typedef enum {
    KeyCode_Unknown1 = 0, 
        
    KeyCode_A = 4, 
    KeyCode_B, 
    KeyCode_C, 
    KeyCode_D, 
    KeyCode_E, 
    KeyCode_F, 
    KeyCode_G, 
    KeyCode_H, 
    KeyCode_I, 
    KeyCode_J, 
    KeyCode_K, 
    KeyCode_L, 
    KeyCode_M, 
    KeyCode_N, 
    KeyCode_O, 
    KeyCode_P, 
    KeyCode_Q, 
    KeyCode_R, 
    KeyCode_S, 
    KeyCode_T, 
    KeyCode_U, 
    KeyCode_V, 
    KeyCode_W, 
    KeyCode_X, 
    KeyCode_Y, 
    KeyCode_Z,
        
    KeyCode_Num0, 
    KeyCode_Num1, 
    KeyCode_Num2, 
    KeyCode_Num3, 
    KeyCode_Num4,
    KeyCode_Num5, 
    KeyCode_Num6, 
    KeyCode_Num7, 
    KeyCode_Num8, 
    KeyCode_Num9,
        
    KeyCode_Enter,
    KeyCode_Escape,
    KeyCode_Backspace, 
    KeyCode_Tab,       
    KeyCode_Space,     
    KeyCode_Minus, 
    KeyCode_Equals,    
    KeyCode_LeftBrac,     
    KeyCode_RightBrac, 
    KeyCode_Backslash,
    KeyCode_Unknown2, 
    KeyCode_Semicolon, 
    KeyCode_Apostrophe, 
    KeyCode_Grave,     
    KeyCode_Comma,     
    KeyCode_Period, 
    KeyCode_Slash,     
    KeyCode_CapsLock,

    KeyCode_F1, 
    KeyCode_F2, 
    KeyCode_F3,  
    KeyCode_F4,  
    KeyCode_F5,  
    KeyCode_F6, 
    KeyCode_F7, 
    KeyCode_F8, 
    KeyCode_F9, 
    KeyCode_F10, 
    KeyCode_F11, 
    KeyCode_F12,

    KeyCode_PrintScreen, 
    KeyCode_ScrollLock, 
    KeyCode_Pause,
    KeyCode_Insert,      
    KeyCode_Home,       
    KeyCode_PageUp, 
    KeyCode_Delete,         
    KeyCode_End,        
    KeyCode_PageDown, 
    KeyCode_Right,       
    KeyCode_Left,       
    KeyCode_Down, 
    KeyCode_Up,

    KeyCodeTotalCount
} KeyCode;

/* Button Codes */
typedef enum {
    ButtonCode_Left, 
    ButtonCode_Middle, 
    ButtonCode_Right, 
    ButtonCode_X1, 
    ButtonCode_X2,

    ButtonCodeTotalCount
} ButtonList;

/* Functions and Structs */
typedef struct {
    bool IsPressed;
    bool IsReleased;
    bool IsHeld;
} KeyState;

typedef struct {
    bool IsDown;
    bool IsUp;
} MouseState;

SDL_Event *Input_GetEventHandler();
void Input_ResetStates();
void Input_UpdateStates();

KeyState Input_GetKey(int key_code);
MouseState Input_GetMouseButton(int button_code);
Vector2i Input_GetMousePos();
Vector2f Input_GetRelativeMousePos();
int Input_MouseScrollHorizontal();
int Input_MouseScrollVertical();

bool Input_KeyPressed(int key_code);
bool Input_KeyReleased(int key_code);
bool Input_KeyHeld(int key_code);
bool Input_ButtonDown(int button_code);
bool Input_ButtonUp(int button_code);