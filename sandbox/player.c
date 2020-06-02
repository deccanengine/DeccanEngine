#include "player.h"

bool selected = false;
Vector2i offset;

SpriteAsset tar;

void action(GameObject *this) {
    if(Collision_ObjectObject(Object_GetObject("main player"), this)) { 
        Color *c = OBJECT_GetComponent(Object_GetObject("main player"), Color);
        *c = ColorList_Green;
    }
}

void _player_begin(GameObject *this) {
    OBJECT_AddComponent(this, Color);
    Color *color = OBJECT_GetComponent(this, Color);
    color->r = 255;
    color->g = 0;
    color->b = 0;
    color->a = 255;

    OBJECT_AddComponent(this, Position);
    Position *position = OBJECT_GetComponent(this, Position);
    position->x = 100;
    position->y = 100;

    OBJECT_AddComponent(this, Collider);
    Collider *collider = OBJECT_GetComponent(this, Collider);
    collider->type = ColliderRect;
    collider->rect = (PosRect){0, 0, 50, 50};
}

void _player_step(GameObject *this) {
    static int32_t SpeedModifier = 5;

    Position *position = OBJECT_GetComponent(this, Position);
    Color *color = OBJECT_GetComponent(this, Color);
    
    if(Input_KeyHeld(KeyCode_W)){ position->y -= SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_S)){ position->y += SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_A)){ position->x -= SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_D)){ position->x += SpeedModifier; }

    if(Input_KeyReleased(KeyCode_Left)) {
        SpeedModifier -= 1;
    }
    else if(Input_KeyReleased(KeyCode_Right)) {
        SpeedModifier += 1;
    }

    /* Center the camera on player */
    //Camera_CenterOn(this);

    Vector2f pos = Input_GetRelativeMousePos();
    if(Collision_ObjectVec(this, &pos)) { 
        *color = ColorList_Orange;
        if(Input_ButtonDown(ButtonCode_Left)) {
            selected = true;
            offset.x = pos.x - position->x;
            offset.y = pos.y - position->y;
        }
        else if(Input_ButtonUp(ButtonCode_Left)) { 
            selected = false; 
        }
    }
    
    if(selected) {
        position->x = pos.x - offset.x;
        position->y = pos.y - offset.y;
    }
    
    Object_GetObjectOfType("static", action);
    
    ECSystem_UpdateSystems(this, SYSTEM_AT_STEP);
}

void _player_render(GameObject *this) {
    Color *color = OBJECT_GetComponent(this, Color);
    Position *position = OBJECT_GetComponent(this, Position);
    
    Draw_FilledRect((Rect){position->x, position->y, 50, 50}, *color);
}

void _player_end(GameObject *this) { }

void _none_begin(GameObject *this) {
    OBJECT_AddComponent(this, Position);
    Position *position = OBJECT_GetComponent(this, Position);

    Position *player_pos = OBJECT_GetComponent(Object_GetObject("main player"), Position);
    position->x = player_pos->x;
    position->y = player_pos->y;

    OBJECT_AddComponent(this, Collider);
    Collider *collider = OBJECT_GetComponent(this, Collider);
    collider->type = ColliderRect;
    collider->rect = (PosRect){0, 0, 40, 40};
}

void _none_step(GameObject *this) { }

void _none_render(GameObject *this) {
    Position *position = OBJECT_GetComponent(this, Position);
    
    Draw_FilledRect((Rect){position->x, position->y, 40, 40}, ColorList_Red); 
}

void _none_end(GameObject *this) { }