#include "player.h"

bool selected = false;
vec2 offset;

DeccanSpriteAsset tar;

Color
    ColorList_White     = (Color){255, 255, 255, 255},
    ColorList_Black     = (Color){  0,   0,   0, 255},
    ColorList_Red       = (Color){255,   0,   0, 255},
    ColorList_Green     = (Color){  0, 255,   0, 255},
    ColorList_Orange    = (Color){255, 165,   0, 255};

void action(GameObject *this) {
    GameObject *player = Scene_GetObject("main player");
    if(Collider_CheckObject(player, this)) {
        Color *color = Object_GetComponent(player, "Color");
        *color = ColorList_Green;
    }
}

void _player_begin(GameObject *this) {
    DE_Var_New(&this->vars, "test", DECCAN_VARTYPE_NUMBER);
    DE_Var_SetNumber(&this->vars, "test", 10080.0f);

    Object_SetComponent(this, "Color", &(Color){255, 0, 0, 255});

    Object_SetComponent(this, "Collider", &(Collider){
        .type = COLLIDER_Rect,
        .rect = {
            [0] = 0,
            [1] = 0,
            [2] = 50,
            [3] = 50
        }
    });

    Object_SetComponent(this, "State2D", &(State2D){
        .position = {
            [0] = 200,
            [1] = 200
        }
    });
}

void _player_step(GameObject *this) {
    static int32_t SpeedModifier = 5;

    State2D *state = Object_GetComponent(this, "State2D");
    Color *color = Object_GetComponent(this, "Color");

    if(Input_KeyHeld(KeyCode_W)){ state->position[1] -= SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_S)){ state->position[1] += SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_A)){ state->position[0] -= SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_D)){ state->position[0] += SpeedModifier; }

    if(Input_KeyReleased(KeyCode_O)) {
        SpeedModifier -= 1;
    }
    else if(Input_KeyReleased(KeyCode_P)) {
        SpeedModifier += 1;
    }

    /* Center the camera on player */
    //Camera_CenterOn(this);

    vec2 pos;
    Input_GetMousePos(pos);
    if(Collider_CheckObjectWithVector(this, pos)) {
        *color = ColorList_Orange;
        if(Input_ButtonDown(ButtonCode_Left)) {
            selected = true;
            offset[0] = pos[0] - state->position[0];
            offset[1] = pos[1] - state->position[1];
        }
        else if(Input_ButtonUp(ButtonCode_Left)) {
            selected = false;
        }
    }

    if(selected) {
        state->position[0] = pos[0] - offset[0];
        state->position[1] = pos[1] - offset[1];
    }

    Scene_IterateObjectOfType("isEnemy", action);
}

void _player_render(GameObject *this) {
    Color *color = Object_GetComponent(this, "Color");
    State2D *state = Object_GetComponent(this, "State2D");

    Draw_FilledRect((vec4){state->position[0], state->position[1], 50, 50}, *color);
}

void _player_end(GameObject *this) { DE_UNUSED(this); }

void _none_begin(GameObject *this) {
    State2D *statePlayer = Object_GetComponent(Scene_GetObject("main player"), "State2D");

    Object_SetComponent(this, "State2D", &(State2D){
        .position = {
            [0] = statePlayer->position[0],
            [1] = statePlayer->position[1]
        }
    });

    Object_SetComponent(this, "Collider", &(Collider){
        .type = COLLIDER_Rect,
        .rect = {
            [0] = 0,
            [1] = 0,
            [2] = 40,
            [3] = 40
        }
    });

    Object_SetTag(this, "isEnemy");
}

void _none_step(GameObject *this) { DE_UNUSED(this); }

void _none_render(GameObject *this) {
    State2D *state = Object_GetComponent(this, "State2D");

    Draw_FilledRect((vec4){state->position[0], state->position[1], 40, 40}, ColorList_Red);
}

void _none_end(GameObject *this) { DE_UNUSED(this); }
