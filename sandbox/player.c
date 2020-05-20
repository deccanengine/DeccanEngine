#include "player.h"

bool selected = false;
Vector2i offset;

TextureAsset tar;

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
    //tar.texture = SDL_CreateTexture(Renderer_GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mode.x, mode.y);
}

void _player_step(GameObject *this) {
    int mod = 5;

    if(Input_KeyHeld(KeyCode_W)){ this->position.y -= mod; }
    else if(Input_KeyHeld(KeyCode_S)){ this->position.y += mod; }
    else if(Input_KeyHeld(KeyCode_A)){ this->position.x -= mod; }
    else if(Input_KeyHeld(KeyCode_D)){ this->position.x += mod; }

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
    Draw_FilledRect((Rect){this->position.x, this->position.y, this->size.y, this->size.y}, this->color);

    Texture_BlitScaled((Rect){this->position.x, this->position.y, 0, 0},
                               (Vector2f){2.0f, 2.0f},
                               (this->angle+90.0f), FlipVertical, Asset_GetTexture("arrow0"));

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