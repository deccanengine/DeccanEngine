#include "player.h"

bool selected = false;
Vector2i offset;

DE_Texture *tar;

void action(GameObject *this) {
    if(Collision.TestFrom(Object.GetObject("main player"), this)) { 
        Object.GetObject("main player")->color = ColorList.green;
        this->SendMessage(this, "hello");
    }
}

void _player_begin(GameObject *this) {
    this->position.x = 100;
    this->position.y = 100;

    this->size.x = 50;
    this->size.y = 50;

    this->collider = Collision.NewRectCollider((PosRect){0, 0, 50, 50});
    //this->collider = Collision.new_circle_collider((Circle){0, 0, 50});
    this->color = ColorList.blue;

    Vector2i mode = Core.GetMode();
    //tar = SDL_CreateTexture(Core.GetGlobalEngine()->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mode.x, mode.y);
}

void _player_step(GameObject *this) {
    int mod = 5;

    if(Input.KeyHeld(Key.w)){ this->position.y -= mod; }
    else if(Input.KeyHeld(Key.s)){ this->position.y += mod; }
    else if(Input.KeyHeld(Key.a)){ this->position.x -= mod; }
    else if(Input.KeyHeld(Key.d)){ this->position.x += mod; }

    /* Center the camera on player */
    Camera.CenterOn(this);

    Vector2f pos = Input.GetRelativeMousePos();
    if(Collision.TestVecFrom(this, &pos)) { 
        this->color = ColorList.fuchsia;
        if(Input.ButtonDown(Button.left)) {
            selected = true;
            offset.x = pos.x - this->position.x;
            offset.y = pos.y - this->position.y;
        }
        else if(Input.ButtonUp(Button.left)) { selected = false; }
    }
    
    /* Modify the color on mouse wheel */
    this->color.g += 10 * Input.MouseScrollVertical();
    
    if(selected) {
        this->position.x = pos.x - offset.x;
        this->position.y = pos.y - offset.y;
    }

    Object.GetObjectOfType("static", action);
}

void _player_render(GameObject *this) {
    Vector2f pos = Input.GetRelativeMousePos();
    double angle = atan2(pos.y - this->position.y, pos.x - this->position.x)*180/3.14159;

    Renderer.DrawRect((Rect){this->position.x, this->position.y, this->size.y, this->size.y}, this->color);

    Renderer.TextureBlitScaled((DE_Rect){this->position.x, this->position.y, 0, 0},
                               (Vector2f){2.0f, 2.0f},
                               (angle+90.0f), FlipVertical, Asset.GetTexture("arrow0"));

    /*Renderer.SetTarget(tar);
    Renderer.Clear(ColorList.white);

    Renderer.SetBlendMode(BlendMode_Alpha);

    Renderer.DrawRect((Rect){this->position.x, this->position.y, this->size.y, this->size.y}, this->color);
    Renderer.draw_circle((Circle){this->position.x, this->position.y, 50}, true, this->color);
    Renderer.TextureDrawWithScale((Vector2i){this->position.x, this->position.y}, (Vector2f){2.0f, 2.0f}, Asset.GetTexture("arrow0"));

    Renderer.SetTarget(NULL);
    Info *engine = Core.GetGlobalEngine();
    
    SDL_RenderCopyEx(engine->renderer, tar, NULL, NULL, 0, NULL, 0);

    Renderer.SetBlendMode(BlendMode_None);
    */
}

void _player_end(GameObject *this) { }

void _none_begin(GameObject *this) {
    this->collider = Collision.NewRectCollider((PosRect){0, 0, 40, 40});
}

void _none_step(GameObject *this) { }

void _none_render(GameObject *this) {
    if(this->ReceiveMessage(this, "hello")) {
        // do nothing, or!
    }
    Renderer.DrawRect((Rect){this->position.x, this->position.y, 40, 40}, ColorList.red); 
}

void _none_end(GameObject *this) { }