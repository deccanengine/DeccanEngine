#include "deccan.h"

void begin(deccan_info *engine) {
    /* Start here */
}

int x = 10, y = 10;

void step(deccan_info *engine) {    
    deccan_clear_screen(engine, (deccan_color){255, 255, 255, 255});

    /* Start here */
#ifdef DECCAN_DEBUG
    //const Uint8 *key_states = SDL_GetKeyboardState(NULL);

    if(deccan_key_get(SDL_SCANCODE_UP).is_pressed){ y-=1; }
    else if(deccan_key_get(SDL_SCANCODE_DOWN).is_pressed){ y+=1; }
    else if(deccan_key_get(SDL_SCANCODE_LEFT).is_pressed){ x-=1; }
    else if(deccan_key_get(SDL_SCANCODE_RIGHT).is_pressed){ x+=1; }

    if(deccan_key_get(SDL_SCANCODE_SPACE).is_released) { printf("released\n"); }

    deccan_set_render_color(engine, black);
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