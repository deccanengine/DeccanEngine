#include "player.h"

bool selected = false;
Vector2 offset;

SpriteAsset tar;

void action(GameObject *this) {
    if(Collider_CheckObject(Object_GetObject("main player"), this)) { 
        Color *c = OBJECT_GetComponent(Object_GetObject("main player"), Color);
        *c = ColorList_Green;
    }
}

void _player_begin(GameObject *this) {
    OBJECT_AddComponentCustom(this, Color);
    Color *color = OBJECT_GetComponent(this, Color);
    color->r = 255;
    color->g = 0;
    color->b = 0;
    color->a = 255;

    OBJECT_AddComponent(this, State2D, {
        .position = {
            .x = 200, .y = 200
        }
    });

    OBJECT_AddComponent(this, Collider, { 
        .type = COLLIDER_Rect, 
        .rect = (Rect){0, 0, 50, 50}
    });
}

void _player_step(GameObject *this) {
    static int32_t SpeedModifier = 5;

    State2D *state = Object_GetComponent(this, "State2D");
    Color *color = Object_GetComponent(this, "Color");
    
    if(Input_KeyHeld(KeyCode_W)){ state->position.y -= SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_S)){ state->position.y += SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_A)){ state->position.x -= SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_D)){ state->position.x += SpeedModifier; }

    if(Input_KeyReleased(KeyCode_O)) {
        SpeedModifier -= 1;
    }
    else if(Input_KeyReleased(KeyCode_P)) {
        SpeedModifier += 1;
    }

    /* Center the camera on player */
    //Camera_CenterOn(this);

    Vector2 pos = Input_GetRelativeMousePos();
    if(Collider_CheckObjectWithVector(this, pos)) { 
        *color = ColorList_Orange;
        if(Input_ButtonDown(ButtonCode_Left)) {
            selected = true;
            offset.x = pos.x - state->position.x;
            offset.y = pos.y - state->position.y;
        }
        else if(Input_ButtonUp(ButtonCode_Left)) { 
            selected = false; 
        }
    }
    
    if(selected) {
        state->position.x = pos.x - offset.x;
        state->position.y = pos.y - offset.y;
    }
    
    Object_GetObjectOfType("static", action);
    
    ECSystem_UpdateSystems(this, SYSTEM_AT_STEP);
}

void _player_render(GameObject *this) {
    Color *color = OBJECT_GetComponent(this, Color);
    State2D *state = Object_GetComponent(this, "State2D");
    
    Draw_FilledRect((Rect){state->position.x, state->position.y, 50, 50}, *color);
}

void _player_end(GameObject *this) { }

void _none_begin(GameObject *this) {
    State2D *statePlayer = Object_GetComponent(Object_GetObject("main player"), "State2D");

    OBJECT_AddComponent(this, State2D, {
        .position = {
                .x = statePlayer->position.x,
                .y = statePlayer->position.y
        }
    });

    OBJECT_AddComponent(this, Collider, {
        .type = COLLIDER_Rect,
        .rect = (Rect){0, 0, 40, 40}
    });
}

void _none_step(GameObject *this) {
    ECSystem_UpdateSystems(this, SYSTEM_AT_STEP);
}

void _none_render(GameObject *this) {
    State2D *state = Object_GetComponent(this, "State2D");
    
    Draw_FilledRect((Rect){state->position.x, state->position.y, 40, 40}, ColorList_Red); 
}

void _none_end(GameObject *this) { }