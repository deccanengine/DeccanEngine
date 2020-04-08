#include "core.h"
#include "timer.h"
#include "input.h"

deccan_info global_engine;

void deccan_set_global_engine(deccan_info *engine) {
    global_engine = *engine;
}

deccan_info *deccan_get_global_engine() {
    return &global_engine;
}

int deccan_init(const char *title, int32_t width, int32_t height) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        deccan_error("Could not initialize SDL", sdlerr);
    }

    if(TTF_Init() != 0) {
        deccan_error("Could not initialize SDL2_ttf", ttferr);
    }

    if((global_engine.window = SDL_CreateWindow(
        title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
        )) == NULL) {
            deccan_error("Could not create window", sdlerr);
        }

    if((global_engine.renderer = SDL_CreateRenderer(global_engine.window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        deccan_error("Could not create renderer", sdlerr);
    }

    global_engine.is_running = true;
    global_engine.is_first_frame = true;
    global_engine.required_fps = 60.0f;

    memcpy(deccan_prev_keys, "\0", sizeof(uint8_t)*SDL_NUM_SCANCODES);
    memcpy(deccan_key_states, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

    return 1;
}

void deccan_quit() {
    global_engine.at_end();

    SDL_DestroyRenderer(global_engine.renderer);
    SDL_DestroyWindow(global_engine.window);
    TTF_Quit();
    SDL_Quit();
}

void deccan_run(float required_fps) {
    int frames = 0;
    float fps_avg;

    global_engine.required_fps = required_fps;
    
    deccan_timer fps_timer; deccan_new_timer(&fps_timer);
    deccan_timer frm_timer; deccan_new_timer(&frm_timer);

    deccan_start_timer(&fps_timer);

    while(global_engine.is_running) {
        deccan_start_timer(&frm_timer);

        SDL_PollEvent(&global_engine.event);
        switch(global_engine.event.type) {
            case SDL_QUIT: { global_engine.is_running = false; break; }
            case SDL_KEYDOWN: { 
                if(global_engine.event.key.keysym.sym == SDLK_ESCAPE) { global_engine.is_running = false; }
                break;
            }
        }
        
        memcpy(deccan_prev_keys, deccan_key_states, sizeof(uint8_t)*SDL_NUM_SCANCODES);
        memcpy(deccan_key_states, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

        fps_avg = frames/deccan_get_timer_time(&fps_timer);
        if(fps_avg > 20000) { fps_avg = 0.0f; }

        if(global_engine.is_first_frame) {
            global_engine.at_begining();
            global_engine.is_first_frame = false;
        }
        global_engine.at_step();
        
        SDL_RenderPresent(global_engine.renderer);

        frames++;
        
        int frm_ticks = deccan_get_timer_time_ms(&frm_timer);
		int ticks_per_frame = 1000/global_engine.required_fps; // 60 = limit;

		if(frm_ticks < ticks_per_frame) {
            deccan_delay(ticks_per_frame - frm_ticks);
		}
#ifdef DECCAN_DEBUG
        printf("FPS Avg: %f\n", fps_avg);
#endif
    }
    deccan_quit();
}

void deccan_set_states(state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae)) {
    global_engine.at_begining = ab;
    global_engine.at_step = as;
    global_engine.at_end = ae;
}