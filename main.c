#include "deccan.h"

void begin() {
    /* Start here */
}

int x = 100, y = 100;

void step() {    
    deccan_clear_screen((deccan_color){255, 255, 255, 255});

    /* Start here */
#ifdef DECCAN_DEBUG
    if(deccan_key_get(SDL_SCANCODE_UP).is_held){ y-=1; }
    else if(deccan_key_get(SDL_SCANCODE_DOWN).is_held){ y+=1; }
    else if(deccan_key_get(SDL_SCANCODE_LEFT).is_held){ x-=1; }
    else if(deccan_key_get(SDL_SCANCODE_RIGHT).is_held){ x+=1; }
    
    deccan_mouse_pos pos = deccan_mouse_get_pos();
    if(pos.x > x && pos.x < x+50 && pos.y > y && pos.y < y+50) {
        if(deccan_mouse_get(SDL_BUTTON_LEFT).is_down) {
            deccan_set_render_color((deccan_color){0, 255, 0, 255});
        }
        else { deccan_set_render_color((deccan_color){0, 180, 0, 255}); }
    }
    else {
        deccan_set_render_color(black);
    }
    SDL_RenderFillRect(deccan_get_global_engine()->renderer, &(SDL_Rect){x, y, 50, 50});
#endif
}

void end() {
    /* Start here */
}

int main(int argc, char **argv) {
    if(deccan_init("Test", 640, 320)) {
        deccan_add_scene(deccan_new_scene("scene0", begin, step, end));
        deccan_run(120.0f);
    }
    atexit(deccan_quit);
}