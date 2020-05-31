#include "player.h"

bool selected = false;
Vector2i offset;

SpriteAsset tar;

typedef struct {
    int32_t mod;
} SpeedModifier;

//typedef Vector2f Position;
typedef Vector2f Velocity;

void ColorFunc(GameObject *obj) {
    Color *c = OBJECT_GetComponent(obj, Color);
    c->r += 10 * Input_MouseScrollVertical();
    if(c->r < 0) {
        c->r = 255;
    }
    if(c->r > 255) {
        c->r = 0;
    }
}

void action(GameObject *this) {
    if(Collision_ObjectObject(Object_GetObject("main player"), this)) { 
        Color *c = OBJECT_GetComponent(Object_GetObject("main player"), Color);
        *c = ColorList_Green;
        
        this->SendMessage(this, "hello");
    }
}

void _player_begin(GameObject *this) {
    /*this->position.x = 100;
    this->position.y = 100;

    this->size.x = 50;
    this->size.y = 50;

    this->collider = Collision_NewRectCollider((PosRect){0, 0, 50, 50});
    //this->collider = Collision.new_circle_collider((Circle){0, 0, 50});
    this->color = ColorList_Blue;

    Vector2i mode = Core_GetMode();
    */

    /* A easy fix for not letting any component use the index: 0    */
    /* The zero index cannot be 'AND' and is taken as no component  */
    //ECSystem_RegisterComponent("NULL");

    const char *ColorComp[] = { "Color" };
    ECSystem_RegisterSystem(1, ColorComp, SYSTEM_AT_STEP, &ColorFunc);

    OBJECT_AddComponent(this, Color);
    Color *thisColor = OBJECT_GetComponent(this, Color);
    thisColor->r = 255;
    thisColor->g = 0;
    thisColor->b = 0;
    thisColor->a = 255;

    OBJECT_AddComponent(this, Position);
    Position *thisPosition = OBJECT_GetComponent(this, Position);
    thisPosition->x = 100;
    thisPosition->y = 100;

    OBJECT_AddComponent(this, Collider);
    Collider *thisCollider = OBJECT_GetComponent(this, Collider);
    thisCollider->type = ColliderRect;
    thisCollider->rect = (PosRect){0, 0, 50, 50};

    //tar.texture = SDL_CreateTexture(Renderer_GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mode.x, mode.y);
}

void _player_step(GameObject *this) {
    static int32_t SpeedModifier = 5;

    Position *thisPosition = OBJECT_GetComponent(this, Position);
    Color *thisColor = OBJECT_GetComponent(this, Color);
    
    if(Input_KeyHeld(KeyCode_W)){ thisPosition->y -= SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_S)){ thisPosition->y += SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_A)){ thisPosition->x -= SpeedModifier; }
    else if(Input_KeyHeld(KeyCode_D)){ thisPosition->x += SpeedModifier; }

    if(Input_KeyReleased(KeyCode_Left)) {
        SpeedModifier -= 1;
    }
    // Issue: using else here causes it to
    // crash with segmentation fault
    if(Input_KeyReleased(KeyCode_Right)) {
        SpeedModifier += 1;
    }

    /* Center the camera on player */
    //Camera_CenterOn(this);

    Vector2f pos = Input_GetRelativeMousePos();
    if(Collision_ObjectVec(this, &pos)) { 
        *thisColor = ColorList_Orange;
        if(Input_ButtonDown(ButtonCode_Left)) {
            selected = true;
            offset.x = pos.x - thisPosition->x;
            offset.y = pos.y - thisPosition->y;
        }
        else if(Input_ButtonUp(ButtonCode_Left)) { 
            selected = false; 
        }
    }
    
    if(selected) {
        thisPosition->x = pos.x - offset.x;
        thisPosition->y = pos.y - offset.y;
    }
    
    Object_GetObjectOfType("static", action);
    /*
    Object_RotateTowardsPosition(this, Input_GetRelativeMousePos(), 1);
    */
    ECSystem_UpdateSystems(this, SYSTEM_AT_STEP);
}

void _player_render(GameObject *this) {
    Color *thisColor = OBJECT_GetComponent(this, Color);
    Position *thisPosition = OBJECT_GetComponent(this, Position);
    
    Draw_FilledRect((Rect){thisPosition->x, thisPosition->y, 50, 50}, *thisColor);

    //Draw_FilledRect((Rect){this->position.x, this->position.y, this->size.y, this->size.y}, *thisColor);

    /*Sprite_BlitScaled((Rect){this->position.x, this->position.y, 0, 0},
                               (Vector2f){2.0f, 2.0f},
                               (this->angle+90.0f), FlipVertical, Asset_GetSprite("arrow0"));
    */
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
    OBJECT_AddComponent(this, Position);
    Position *p = OBJECT_GetComponent(this, Position);

    Position *o = OBJECT_GetComponent(Object_GetObject("main player"), Position);
    p->x = o->x;
    p->y = o->y;

    OBJECT_AddComponent(this, Collider);
    Collider *c = OBJECT_GetComponent(this, Collider);
    c->type = ColliderRect;
    c->rect = (PosRect){0, 0, 40, 40};

    //this->collider = Collision_NewRectCollider((PosRect){0, 0, 40, 40});
}

void _none_step(GameObject *this) { }

void _none_render(GameObject *this) {
    if(this->ReceiveMessage(this, "hello")) {
        // do nothing, or!
    }

    Position *p = OBJECT_GetComponent(this, Position);
    
    Draw_FilledRect((Rect){p->x, p->y, 40, 40}, ColorList_Red); 
    /*Object.RotateTowardsObject(this, Object.GetObject("main player"), 1);
    Renderer.TextureBlitScaled((Rect){this->position.x, this->position.y, 0, 0},
                               (Vector2f){2.0f, 2.0f},
                               (this->angle), FlipVertical, Asset.GetTexture("arrow0"));*/

    //printf("angle: %f\n", this->angle);
}

void _none_end(GameObject *this) { }