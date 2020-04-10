#define using_namespace_deccan
#include "deccan.h"

void begin() {
    /* Start here */
    asset_load_texture("arrow", "arrow0.png");
}

int x = 100, y = 100;

void step() {
    renderer_clear((Color){255, 255, 255, 255});

    /* Start here */
#ifdef DECCAN_DEBUG
    if(input_get_key(SDL_SCANCODE_UP).is_held){ y-=1; }
    else if(input_get_key(SDL_SCANCODE_DOWN).is_held){ y+=1; }
    else if(input_get_key(SDL_SCANCODE_LEFT).is_held){ x-=1; }
    else if(input_get_key(SDL_SCANCODE_RIGHT).is_held){ x+=1; }
    
    MousePos pos = input_get_mouse_pos();
    if(pos.x > x && pos.x < x+50 && pos.y > y && pos.y < y+50) {
        if(input_get_mouse_button(SDL_BUTTON_LEFT).is_down) {
            renderer_set_color((Color){0, 255, 0, 255});
        }
        else { renderer_set_color((Color){0, 180, 0, 255}); }
    }
    else {
        renderer_set_color(black);
    }
    SDL_RenderFillRect(get_global_engine()->renderer, &(SDL_Rect){x, y, 50, 50});
    
    int w, h;
    SDL_Texture *tex = asset_get_texture("arrow");
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_RenderCopy(get_global_engine()->renderer, tex, NULL, &(SDL_Rect){x, y, w, h});
#endif
}

void end() {
    /* Start here */
}

int main(int argc, char **argv) {
    if(init("Test", 640, 320)) {
        add_scene(new_scene("scene0", begin, step, end), false);
        run(120.0f);
    }
    atexit(quit);
}