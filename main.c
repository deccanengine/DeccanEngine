#include "deccan.h"

void begin(deccan_info *engine) {
    /* Start here */
}

int x = 100, y = 100;

void step(deccan_info *engine) {    
    deccan_clear_screen(engine, (deccan_color){255, 255, 255, 255});

    /* Start here */
#ifdef DECCAN_DEBUG
    if(deccan_key_get(SDL_SCANCODE_UP).is_held){ y-=1; }
    else if(deccan_key_get(SDL_SCANCODE_DOWN).is_held){ y+=1; }
    else if(deccan_key_get(SDL_SCANCODE_LEFT).is_held){ x-=1; }
    else if(deccan_key_get(SDL_SCANCODE_RIGHT).is_held){ x+=1; }

    deccan_mouse_pos pos = deccan_mouse_get_pos();
    if(pos.x > x && pos.x < x+50 && pos.y > y && pos.y < y+50) {
        if(deccan_mouse_get(engine, SDL_BUTTON_LEFT).is_down) {
            deccan_set_render_color(engine, (deccan_color){0, 255, 0, 255});
        }
        else { deccan_set_render_color(engine, (deccan_color){0, 180, 0, 255}); }
    }
    else {
        deccan_set_render_color(engine, black);
    }
    SDL_RenderFillRect(engine->renderer, &(SDL_Rect){x, y, 50, 50});
#endif
}

void end(deccan_info *engine) {
    /* Start here */
}

deccan_info game;
void at_exit_func() { deccan_quit(&game); }

int main(int argc, char **argv) {
    if(deccan_init(&game, "Test", 640, 320)) {
        deccan_set_states(&game, begin, step, end);
        deccan_run(&game, 120.0f);
    }

    atexit(at_exit_func);
}