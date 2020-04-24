/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

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

int _priv_Core_init(const char *title, Deccan_Vector2i mode) {
    int flags = SDL_INIT_VIDEO;
    if(SDL_Init(flags) != 0) {
        DE_error("Could not initialize SDL2: %s", SDL_GetError());
    }

    int image_flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if(!IMG_Init(image_flags) & !image_flags) {
        DE_error("Could not initialize SDL2_image: %s", IMG_GetError());
    }

    if(TTF_Init() != 0) {
        DE_error("Could not initialize SDL2_ttf: %s", TTF_GetError());
    }

    int window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    if((global_engine.window = SDL_CreateWindow(title, 0, 0, mode.x, mode.y, window_flags)) == NULL) {
        DE_error("Could not create window: %s", SDL_GetError());
    }

    int render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    if((global_engine.renderer = SDL_CreateRenderer(global_engine.window, -1, render_flags)) == NULL) {
        DE_error("Could not create renderer: %s", SDL_GetError());
    }

    DE_logfile = fopen("report.log", "w");
    if(DE_logfile == NULL) {
        DE_error("Could not create/open log file");
    }

    global_engine.win_mode = mode;
    global_engine.is_running = true;
    global_engine.vsync_enabled = false;
    global_engine.fps_req = 60.0f;      /* Fallback FPS limit if vsync is disabled somwhere and new limit is not set */

    global_engine.scenes = NULL;
    global_engine.scene_count = 0;

    global_engine.textures = NULL;

    memcpy(global_engine.prev_keys, "\0", sizeof(uint8_t)*SDL_NUM_SCANCODES);
    memcpy(global_engine.curr_keys, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

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
    int frames = 0;         /* Total frames passed */
    Deccan_Timer fps_timer = Deccan_Clock.new_timer();
    Deccan_Timer frm_timer = Deccan_Clock.new_timer();

    fps_timer.start(&fps_timer);    /* To calculate FPS */

    /* If no FPS limit is set then enable VSync*/
    if(fps <= 0.0f) { Deccan_Core.set_vsync_status(true); }
    else { Deccan_Core.set_vsync_status(false); }
    
    /* Set FPS limit if VSync is not enabled */
    /* There is no gurantee than VSync is enabled by set_vsync_status().
     * Hence, it is separated. 
     */
    if(!global_engine.vsync_enabled) { global_engine.fps_req = fps; }

    while(global_engine.is_running) {
        if(!global_engine.vsync_enabled) { frm_timer.start(&frm_timer); }

        /* Handle some events */
        if(SDL_PollEvent(&global_engine.event)) {
            switch(global_engine.event.type) {
                case SDL_QUIT: { global_engine.is_running = false; break; }
                case SDL_KEYDOWN: {
                    /* Close on Escape Key */
                    // To do: make it toggleable
                    if(global_engine.event.key.keysym.sym == SDLK_ESCAPE) { 
                        global_engine.is_running = false; break;
                    }
                }
            }
        }
        
        /* Get and set current and key states*/
        memcpy(global_engine.prev_keys, global_engine.curr_keys, sizeof(uint8_t)*SDL_NUM_SCANCODES);
        memcpy(global_engine.curr_keys, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

        /* Calculate FPS */
        global_engine.fps_avg = frames/fps_timer.get_time(&fps_timer);
        if(global_engine.fps_avg > 20000) { global_engine.fps_avg = 0.0f; }

        /* Process Scene(s) and GameObject(s) */
        int index = global_engine.scene_count-1;        /* Current Scene index */
        Deccan_Scene *scene = global_engine.scenes[index];  /* Current scene */
        /* First frame of the scene. Same as at_beginning for scene */
        if(scene->is_first_frame == true) {
            scene->at_first_frame();
            scene->is_first_frame = false;

            /* First frame of objects */
            for(int i=0; i<scene->object_count; i++) {
                Deccan_GameObject *obj = scene->objects[i];
                obj->at_first_frame(obj);
            }
        }

        /* at_beginning of objects */
        for(int i=0; i<scene->object_count; i++) {
            Deccan_GameObject *obj = scene->objects[i];
            if(obj->is_beginning) {
                obj->at_beginning(obj);
                obj->is_beginning = false;
            }
        }

        /* at_step of scenes and objects */
        scene->at_step();
        for(int i=0; i<scene->object_count; i++) {
            Deccan_GameObject *obj = scene->objects[i];
            obj->at_step(obj);
        }

        /* at_render of scenes and objects */
        scene->at_render();
        for(int i=0; i<scene->object_count; i++) {
            Deccan_GameObject *obj = scene->objects[i];
            obj->at_render(obj);
        }
        
        SDL_RenderPresent(global_engine.renderer);

        /* Prevent mouse wheel scroll input spam */
        global_engine.event.wheel.x = 0;
        global_engine.event.wheel.y = 0;

        frames++;
        
        /* Limit FPS */
        if(!global_engine.vsync_enabled && global_engine.fps_req > 0.0f) {
            if(!frm_timer.is_running) { continue; }

            int frm_ticks = frm_timer.get_time_ms(&frm_timer);  /* Current ticks per frame */
            int ticks_per_frame = 1000/global_engine.fps_req;   /* Required ticks per frame */

            if(frm_ticks < ticks_per_frame) {
                Deccan_Clock.delay(ticks_per_frame - frm_ticks);
            }
        }
    }
    
    /* at_end of scenes and objects */
    Deccan_Scene *scene = global_engine.scenes[global_engine.scene_count-1];
    scene->at_end();
    for(int i=0; i<scene->object_count; i++) {
        Deccan_GameObject *obj = scene->objects[i];
        obj->at_end(obj);
    }
    
    Deccan_Core.quit();
}

/* Core Settings Setters */
void _priv_Core_set_title(const char *name) {
    SDL_SetWindowTitle(global_engine.window, name);
}

void _priv_Core_set_mode(Deccan_Vector2i mode) {
    if(global_engine.is_fullscreen) {
        SDL_DisplayMode disp = {SDL_PIXELFORMAT_UNKNOWN, mode.x, mode.y, 0, 0};
        if(SDL_SetWindowDisplayMode(global_engine.window, &disp) > 0) {
            DE_report("Cannot set fullscreen window mode: %s", SDL_GetError());
        }
        SDL_MaximizeWindow(global_engine.window);
    }
    else { SDL_SetWindowSize(global_engine.window, mode.x, mode.y); }
    global_engine.win_mode = mode;
}

void _priv_Core_set_fullscreen() {
    SDL_SetWindowFullscreen(global_engine.window, global_engine.is_fullscreen ? 0 : 1);
    global_engine.is_fullscreen = !global_engine.is_fullscreen;
}

void _priv_Core_set_vsync_status(bool vsync) {
    // ??: Adaptive vsync
    if(SDL_GL_SetSwapInterval(vsync ? -1 : 0) == -1) {
        DE_report("VSync is not supported: %s", SDL_GetError());
    }

    int status = SDL_GL_GetSwapInterval();
    if(status == 0) { global_engine.vsync_enabled = false; }
    else { global_engine.vsync_enabled = true; }
}

void _priv_Core_set_framerate_limit(float fps){
    global_engine.fps_req = fps;
}

/* Core Settings Getters */
const char *_priv_Core_get_title() {
    return SDL_GetWindowTitle(global_engine.window);
}

Deccan_Vector2i _priv_Core_get_mode() {
    return global_engine.win_mode;
}

bool _priv_Core_get_fullscreen_status() {
    return global_engine.is_fullscreen;
}

bool _priv_Core_get_vsync_status() {
    return global_engine.vsync_enabled;
}

float _priv_Core_get_framerate_limit() {
    return global_engine.fps_req;
}

float _priv_Core_get_average_framerate() {
    return global_engine.fps_avg;
}