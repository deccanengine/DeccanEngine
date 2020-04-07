#include "core.h"
#include "timer.h"

int deccan_init(deccan_info *engine, const char *title, int32_t width, int32_t height) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        deccan_error("Could not initialize SDL", sdlerr);
    }

    if(TTF_Init() != 0) {
        deccan_error("Could not initialize SDL2_ttf", ttferr);
    }

    if((engine->window = SDL_CreateWindow(
        title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
        )) == NULL) {
            deccan_error("Could not create window", sdlerr);
        }

    if((engine->renderer = SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        deccan_error("Could not create renderer", sdlerr);
    }

    engine->is_running = true;
    engine->is_first_frame = true;
    engine->required_fps = 60.0f;

    return 1;
}

void deccan_quit(deccan_info *engine) {
    engine->at_end(engine);

    SDL_DestroyRenderer(engine->renderer);
    SDL_DestroyWindow(engine->window);
    TTF_Quit();
    SDL_Quit();
}

void deccan_run(deccan_info *engine, float required_fps) {
    int frames = 0;
    float fps_avg;

    engine->required_fps = required_fps;
    
    deccan_timer fps_timer; deccan_new_timer(&fps_timer);
    deccan_timer frm_timer; deccan_new_timer(&frm_timer);

    deccan_start_timer(&fps_timer);

    while(engine->is_running) {
        deccan_start_timer(&frm_timer);

        SDL_PollEvent(&engine->event);
        switch(engine->event.type) {
            case SDL_QUIT: { engine->is_running = false; break; }
            case SDL_KEYDOWN: { 
                if(engine->event.key.keysym.sym == SDLK_ESCAPE) { engine->is_running = false; }
                break;
            }
        }

        fps_avg = frames/deccan_get_timer_time(&fps_timer);
        if(fps_avg > 20000) { fps_avg = 0.0f; }

        if(engine->is_first_frame) {
            engine->at_begining(engine);
            engine->is_first_frame = false;
        }
        engine->at_step(engine);
        
        SDL_RenderPresent(engine->renderer);

        frames++;
        
        int frm_ticks = deccan_get_timer_time_ms(&frm_timer);
		int ticks_per_frame = 1000/engine->required_fps; // 60 = limit;

		if(frm_ticks < ticks_per_frame) {
            deccan_delay(ticks_per_frame - frm_ticks);
		}
#ifdef DECCAN_DEBUG
        printf("FPS Avg: %f\n", fps_avg);
#endif
    }
    deccan_quit(engine);
}

void deccan_set_states(deccan_info* engine, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae)) {
    engine->at_begining = ab;
    engine->at_step = as;
    engine->at_end = ae;
}