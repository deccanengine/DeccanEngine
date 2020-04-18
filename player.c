#include "player.h"

bool selected = false;

Color col;
Vector2i offset;

void _player_begin(GameObject *this) {
    this->position.x = 100;
    this->position.y = 100;
    this->collider = Collision.new_rect_collider((PosRect){0, 0, 50, 50});
}

void _player_step(GameObject *this) {
    int mod = 5;

    if(Input.key_held(Key.w)){ this->position.y -= mod; }
    else if(Input.key_held(Key.s)){ this->position.y += mod; }
    else if(Input.key_held(Key.a)){ this->position.x -= mod; }
    else if(Input.key_held(Key.d)){ this->position.x += mod; }
    
    Vector2i pos = Input.get_mouse_pos();
    
    if(Collision.test_vec(this, pos)) { 
        col = ColorList.fuchsia;
        if(Input.button_down(Button.left)) {
            selected = true;
            offset.x = pos.x - this->position.x;
            offset.y = pos.y - this->position.y;
        }
        else if(Input.button_up(Button.left)) { selected = false; }
    }
    else { col = ColorList.black; }
    
    if(selected) {
        this->position.x = pos.x - offset.x;
        this->position.y = pos.y - offset.y;
    }
}

void _player_render(GameObject *this) {
    Renderer.draw_rect((Rect){this->position.x, this->position.y, 50, 50}, true, col);
    Renderer.draw_circle((Vector3i){this->position.x+100, this->position.y+100, 50}, true, col);
    Renderer.draw_scaled_texture((Vector2i){this->position.x+200, this->position.y+200}, (Vector2f){2.0f, 2.0f}, Asset.get_texture("arrow"));
}

void _player_end(GameObject *this) { }