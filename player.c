#include "player.h"

bool selected = false;
Vector2i offset;

void action(GameObject *this) {
    if(Collision.test_from(Object.get_object("main player"), this)) { 
        Object.get_object("main player")->color = ColorList.green;
    }
}

void _player_begin(GameObject *this) {
    this->position.x = 100;
    this->position.y = 100;
    this->collider = Collision.new_rect_collider((PosRect){0, 0, 50, 50});
    //this->collider = Collision.new_circle_collider((Circle){0, 0, 50});
}

void _player_step(GameObject *this) {
    int mod = 5;

    if(Input.key_held(Key.w)){ this->position.y -= mod; }
    else if(Input.key_held(Key.s)){ this->position.y += mod; }
    else if(Input.key_held(Key.a)){ this->position.x -= mod; }
    else if(Input.key_held(Key.d)){ this->position.x += mod; }

    /* Center the camera on player */
    Vector2i mode = Core.get_mode();
    Camera.set_position((Vector2i){this->position.x + 25 - mode.x/2, this->position.y + 25 - mode.y/2});
    
    Vector2i pos = Input.get_mouse_pos();
    if(Collision.test_vec_from(this, pos)) { 
        this->color = ColorList.fuchsia;
        if(Input.button_down(Button.left)) {
            selected = true;
            offset.x = pos.x - this->position.x;
            offset.y = pos.y - this->position.y;
        }
        else if(Input.button_up(Button.left)) { selected = false; }
    }
    else { this->color = ColorList.blue; }
    
    if(selected) {
        this->position.x = pos.x - offset.x;
        this->position.y = pos.y - offset.y;
    }

    Object.get_object_of_type("static", action);
}

void _player_render(GameObject *this) {
    Renderer.draw_rect((Rect){this->position.x, this->position.y, 50, 50}, true, this->color);
    //Renderer.draw_circle((Circle){this->position.x, this->position.y, 50}, true, this->color);
}

void _player_end(GameObject *this) { }

void _none_begin(GameObject *this) {
    this->collider = Collision.new_rect_collider((PosRect){0, 0, 40, 40});
}

void _none_step(GameObject *this) { }

void _none_render(GameObject *this) {
    Renderer.draw_rect((Rect){this->position.x, this->position.y, 40, 40}, true, ColorList.red); 
}

void _none_end(GameObject *this) { }