#define STB_DS_IMPLEMENTATION
#include "core.h"

Deccan_Info global_engine;

/* Core */
void _priv_Core_set_global_engine(Deccan_Info *engine) {
    global_engine = *engine;
}

Deccan_Info *_priv_Core_get_global_engine() {
    return &global_engine;
}

int _priv_Core_init(const char *title, int32_t width, int32_t height) {
    int flags = SDL_INIT_VIDEO;
    if(SDL_Init(flags) != 0) {
        Deccan_error("Could not initialize SDL2", sdlerr);
    }

    int image_flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if(!IMG_Init(image_flags) & !image_flags) {
        Deccan_error("Could not initialize SDL2_image", imgerr);
    }

    if(TTF_Init() != 0) {
        Deccan_error("Could not initialize SDL2_ttf", ttferr);
    }

    int properties = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    if((global_engine.window = SDL_CreateWindow(title, 0, 0, width, height, properties)) == NULL) {
        Deccan_error("Could not create window", sdlerr);
    }

    if((global_engine.renderer = SDL_CreateRenderer(global_engine.window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        Deccan_error("Could not create renderer", sdlerr);
    }

    global_engine.is_running = true;
    global_engine.required_fps = 60.0f;

    global_engine.scenes = NULL;
    global_engine.textures = NULL;

    memcpy(_prev_keys, "\0", sizeof(uint8_t)*SDL_NUM_SCANCODES);
    memcpy(_key_states, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

    return 1;
}

void _priv_Core_quit() {
    stbds_arrfree(global_engine.scenes);

    SDL_DestroyRenderer(global_engine.renderer);
    SDL_DestroyWindow(global_engine.window);
    TTF_Quit();
    SDL_Quit();
}

void _priv_Core_run(float fps) {
    int frames = 0;
    float fps_avg;

    global_engine.required_fps = fps;

    Deccan_Timer fps_timer, frm_timer;
    Deccan_timer_start(&fps_timer);
    while(global_engine.is_running) {
        Deccan_timer_start(&frm_timer);

        SDL_PollEvent(&global_engine.event);
        switch(global_engine.event.type) {
            case SDL_QUIT: { global_engine.is_running = false; break; }
            case SDL_KEYDOWN: {
                if(global_engine.event.key.keysym.sym == SDLK_ESCAPE) { 
                    global_engine.is_running = false; break;
                }
            }
        }
        
        memcpy(_prev_keys, _key_states, sizeof(uint8_t)*SDL_NUM_SCANCODES);
        memcpy(_key_states, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

        fps_avg = frames/Deccan_timer_get_time(&fps_timer);
        if(fps_avg > 20000) { fps_avg = 0.0f; }

        int index = stbds_arrlen(global_engine.scenes)-1;
        if(global_engine.scenes[index]->is_first_frame == true) {
            global_engine.scenes[index]->at_begining();
            global_engine.scenes[index]->is_first_frame = false;
        }
        global_engine.scenes[index]->at_step();
        
        SDL_RenderPresent(global_engine.renderer);

        frames++;
        
        int frm_ticks = Deccan_timer_get_time_ms(&frm_timer);
		int ticks_per_frame = 1000/global_engine.required_fps;

		if(frm_ticks < ticks_per_frame) {
            Deccan_delay(ticks_per_frame - frm_ticks);
		}
    }
    global_engine.scenes[stbds_arrlen(global_engine.scenes)-1]->at_end();
    _priv_Core_quit();
}

void _priv_Core_set_mode(int32_t width, int32_t height) {
    SDL_SetWindowSize(global_engine.window, width, height);
}

void _priv_Core_set_fullscreen() {
    SDL_SetWindowFullscreen(global_engine.window, global_engine.is_fullscreen ? 1 : 0);
    global_engine.is_fullscreen = !global_engine.is_fullscreen;
}

void _priv_Core_set_framerate_limit(float fps){
    global_engine.required_fps = fps;
}

bool _priv_Core_get_fullscreen_status() {
    return global_engine.is_fullscreen;
}

float _priv_Core_get_framerate_limit() {
    return global_engine.required_fps;
}

/* Scene Management */
Deccan_Scene *_priv_Scene_new_scene(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae)) {
    Deccan_Scene *scene = malloc(sizeof(Deccan_Scene));
    
    scene->name = malloc(sizeof(char*)*strlen(name)); strcpy(scene->name, name);
    scene->is_paused = false;
    scene->is_first_frame = true;
    scene->at_begining = ab;
    scene->at_step = as;
    scene->at_end = ae;

    return scene;
}

void _priv_Scene_add_scene(Deccan_Scene *scene, bool is_replacing) {
    if(stbds_arrlen(global_engine.scenes) != 0) {
        if(is_replacing) { stbds_arrpop(global_engine.scenes); }
        else {
            global_engine.scenes[stbds_arrlen(global_engine.scenes)-1]->is_paused = true;
        }
    }
    stbds_arrput(global_engine.scenes, scene);
}

void _priv_Scene_remove_scene(Deccan_Scene *scene) {
    if(stbds_arrlen(global_engine.scenes) > 1) { 
        stbds_arrpop(global_engine.scenes);
        global_engine.scenes[stbds_arrlen(global_engine.scenes)-1]->is_paused = false;
    }
}

Deccan_Scene *_priv_Scene_current_scene() {
    return global_engine.scenes[stbds_arrlen(global_engine.scenes)-1];
}

void _priv_Scene_pause_scene(bool pause) {
    global_engine.scenes[stbds_arrlen(global_engine.scenes)-1]->is_paused = pause;
}

bool _priv_Scene_is_scene_paused() {
    return global_engine.scenes[stbds_arrlen(global_engine.scenes)-1]->is_paused;
}