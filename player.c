#include "player.h"

bool selected = false;

Color col, col2;
Vector2i offset;

void _player_begin(GameObject *this) {
    this->position.x = 100;
    this->position.y = 100;
    this->collider = Collision.new_circle_collider((Circle){0, 0, 50});
}

void _player_step(GameObject *this) {
    int mod = 5;

    if(Input.key_held(Key.w)){ this->position.y -= mod; }
    else if(Input.key_held(Key.s)){ this->position.y += mod; }
    else if(Input.key_held(Key.a)){ this->position.x -= mod; }
    else if(Input.key_held(Key.d)){ this->position.x += mod; }
    
    Vector2i pos = Input.get_mouse_pos();
    
    if(Collision.test_vec_from(this, pos)) { 
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

    if(Collision.test_object("main player", "circle")) { col2 = ColorList.green; } 
    else { col2 = ColorList.blue; }
}

void _player_render(GameObject *this) {
    //Renderer.draw_rect((Rect){this->position.x, this->position.y, 50, 50}, true, col);
    Renderer.draw_circle((Circle){this->position.x, this->position.y, 50}, true, col);
}

void _player_end(GameObject *this) { }

void _none_begin(GameObject *this) {
    this->position.x = 300;
    this->position.y = 100;
    this->collider = Collision.new_circle_collider((Circle){0, 0, 50});
}

void _none_step(GameObject *this) { }

void _none_render(GameObject *this) { 
    Renderer.draw_circle((Circle){this->position.x, this->position.y, 50}, true, col2); 
}

void _none_end(GameObject *this) { }