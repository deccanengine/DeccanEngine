#include "player.h"

bool selected = false;
Vector2i offset;

SpriteAsset tar;

typedef struct {
    int32_t mod;
} SpeedModifier;

typedef Vector2f Position;
typedef Vector2f Velocity;

void action(GameObject *this) {
    if(Collision_ObjectObject(Object_GetObject("main player"), this)) { 
        Object_GetObject("main player")->color = ColorList_Green;
        this->SendMessage(this, "hello");
    }
}

void _player_begin(GameObject *this) {
    this->position.x = 100;
    this->position.y = 100;

    this->size.x = 50;
    this->size.y = 50;

    this->collider = Collision_NewRectCollider((PosRect){0, 0, 50, 50});
    //this->collider = Collision.new_circle_collider((Circle){0, 0, 50});
    this->color = ColorList_Blue;

    Vector2i mode = Core_GetMode();

    /* A easy fix for not letting any component use the index: 0    */
    /* The zero index cannot be 'AND' and is taken as no component  */
    ECSystem_RegisterComponent("NULL");

    /* Register all the components */
    ECSystem_RegisterComponent("Color");
    ECSystem_RegisterComponent("SpeedModifier");
    ECSystem_RegisterComponent("Position");
    ECSystem_RegisterComponent("Velocity");

    const char *comps[] = {
        "SpeedModifier",
        "Position",
        "Velocity",
    };
    ECSystem_RegisterSystem(3, comps);

    // check
    int32_t s0 = ECSystem_GetSystem(0);
    
    const char *comps2[] = {
        "Color",
        "SpeedModifier"
    };
    ECSystem_RegisterSystem(2, comps2);

    // check
    int32_t s1 = ECSystem_GetSystem(1);

    OBJECT_AddComponent(this, Color);
    Color *thisColor = OBJECT_GetComponent(this, Color);
    
    thisColor->r = 0;
    thisColor->g = 0;
    thisColor->b = 0;
    thisColor->a = 255;

    OBJECT_AddComponent(this, SpeedModifier);
    SpeedModifier *thisSpeed = OBJECT_GetComponent(this, SpeedModifier);

    OBJECT_AddComponent(this, Position);

    thisSpeed->mod = 5;

    //tar.texture = SDL_CreateTexture(Renderer_GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mode.x, mode.y);
}

void _player_step(GameObject *this) {
    //int mod = 5;

    SpeedModifier *thisSpeed = OBJECT_GetComponent(this, SpeedModifier);

    if(Input_KeyHeld(KeyCode_W)){ this->position.y -= thisSpeed->mod; }
    else if(Input_KeyHeld(KeyCode_S)){ this->position.y += thisSpeed->mod; }
    else if(Input_KeyHeld(KeyCode_A)){ this->position.x -= thisSpeed->mod; }
    else if(Input_KeyHeld(KeyCode_D)){ this->position.x += thisSpeed->mod; }

    /* Center the camera on player */
    Camera_CenterOn(this);

    Vector2f pos = Input_GetRelativeMousePos();
    if(Collision_ObjectVec(this, &pos)) { 
        this->color = ColorList_Orange;
        if(Input_ButtonDown(ButtonCode_Left)) {
            selected = true;
            offset.x = pos.x - this->position.x;
            offset.y = pos.y - this->position.y;
        }
        else if(Input_ButtonUp(ButtonCode_Left)) { selected = false; }
    }

    /* Component test */
    Color *thisColor = OBJECT_GetComponent(this, Color);
    if(thisColor->r <= 255) {
        thisColor->r += 1;
    }
    else {
        thisColor->r = 0;
    }

    thisSpeed->mod += 1 * Input_MouseScrollVertical();
    /* Component test */

    /* Modify the color on mouse wheel */
    this->color.g += 10 * Input_MouseScrollVertical();
    
    if(selected) {
        this->position.x = pos.x - offset.x;
        this->position.y = pos.y - offset.y;
    }

    Object_GetObjectOfType("static", action);

    Object_RotateTowardsPosition(this, Input_GetRelativeMousePos(), 1);
}

void _player_render(GameObject *this) {
    Color *thisColor = OBJECT_GetComponent(this, Color);

    Draw_FilledRect((Rect){this->position.x, this->position.y, this->size.y, this->size.y}, *thisColor);

    Sprite_BlitScaled((Rect){this->position.x, this->position.y, 0, 0},
                               (Vector2f){2.0f, 2.0f},
                               (this->angle+90.0f), FlipVertical, Asset_GetSprite("arrow0"));

    /*
    Renderer_SetTarget(&tar);
    Renderer_Clear(ColorList.white);

    Draw_Rect((Rect){this->position.x, this->position.y, this->size.y, this->size.y}, this->color);
    Renderer.draw_circle((Circle){this->position.x, this->position.y, 50}, true, this->color);
    Renderer_SetTarget(NULL);
    
    SDL_RenderCopyEx(Renderer_GetRenderer(), tar.texture, NULL, NULL, 67, NULL, 0);
    */
}

void _player_end(GameObject *this) { }

void _none_begin(GameObject *this) {
    this->collider = Collision_NewRectCollider((PosRect){0, 0, 40, 40});
}

void _none_step(GameObject *this) { }

void _none_render(GameObject *this) {
    if(this->ReceiveMessage(this, "hello")) {
        // do nothing, or!
    }
    
    Draw_FilledRect((Rect){this->position.x, this->position.y, 40, 40}, ColorList_Red); 
    /*Object.RotateTowardsObject(this, Object.GetObject("main player"), 1);
    Renderer.TextureBlitScaled((Rect){this->position.x, this->position.y, 0, 0},
                               (Vector2f){2.0f, 2.0f},
                               (this->angle), FlipVertical, Asset.GetTexture("arrow0"));*/

    //printf("angle: %f\n", this->angle);
}

void _none_end(GameObject *this) { }