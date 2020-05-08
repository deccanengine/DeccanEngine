/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#define STB_DS_IMPLEMENTATION
#include <Deccan/Core.h>
#include <Deccan/Renderer.h>

static DE_GameInfo engine;

/* Core */
void DE_Core_SetGlobalInfo(DE_GameInfo *info) {
    engine = *info;
}

DE_GameInfo *DE_Core_GetGlobalInfo() {
    return &engine;
}

int DE_Core_Init(const char *title, DE_Vector2i mode) {
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

#ifdef DECCAN_RENDERER_SDL
    /* GL Attributes: OpenGL 2.1 with hardware acceleration */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    /* Create window */
    int window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    if((engine.window = SDL_CreateWindow(title, 0, 0, mode.x, mode.y, window_flags)) == NULL) {
        DE_error("Could not create window: %s", SDL_GetError());
    }

    /* Set the renderer to OpenGL */
    if(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl") != SDL_TRUE) {
        DE_error("OpenGL cannot be enabled");
    }

    /* Create renderer */
    int render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    if((engine.renderer = SDL_CreateRenderer(engine.window, -1, render_flags)) == NULL) {
        DE_error("Could not create renderer: %s", SDL_GetError());
    }
#else
    
#endif
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &engine.gl_major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &engine.gl_minor);
    if(engine.gl_major < 2 || (engine.gl_major == 2 && engine.gl_minor < 1)) {
        DE_error("OpenGL 2.1 support needed at minimum. Consider upgrading your hardware.");
    }

    /* Open the log file */
    engine.logfile = fopen("report.log", "w");
    if(engine.logfile == NULL) {
        DE_error("Could not create/open log file");
    }

#ifdef DECCAN_RENDERER_SDL
    engine.target = SDL_GetRenderTarget(engine.renderer);
#else

#endif
    engine.is_running = true;

    engine.win_mode = mode;
    engine.vsync_enabled = false;
    engine.fps_req = 60.0f;      /* Fallback FPS limit if vsync is disabled somwhere and new limit is not set */

    engine.scenes = NULL;
    engine.scene_count = 0;

    engine.textures = NULL;
    engine.fonts = NULL;

    engine.camera_bounds = (DE_PosRect){-1, -1, -1, -1};

    DE_msg_init(&engine.msg, DECCAN_MSG_COUNT, DECCAN_MSG_LENGTH);

    memcpy(engine.prev_keys, "\0", sizeof(uint8_t)*SDL_NUM_SCANCODES);
    memcpy(engine.curr_keys, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

    return 1;
}

void DE_Core_Quit() {
    fclose(engine.logfile);
    stbds_arrfree(engine.scenes);
#ifdef DECCAN_RENDERER_SDL
    SDL_DestroyRenderer(engine.renderer);
    SDL_DestroyWindow(engine.window);    
#else
    
#endif
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void DE_Core_Run(float fps) {
    DE_Timer fps_timer = DE_Clock_NewTimer();
    DE_Timer frm_timer = DE_Clock_NewTimer();

    fps_timer.Start(&fps_timer);    /* To calculate FPS */

    /* If no FPS limit is set then enable VSync*/
    if(fps <= 0.0f) { DE_Core_SetVsyncStatus(true); }
    else { DE_Core_SetVsyncStatus(false); }
    
    /* Set FPS limit if VSync is not enabled */
    /* There is no gurantee than VSync is enabled by set_vsync_status().
     * Hence, it is separated. 
     */
    if(!engine.vsync_enabled) { engine.fps_req = fps; }

    while(engine.is_running) {
        frm_timer.Start(&frm_timer);

        /* Handle some events */
        if(SDL_PollEvent(&engine.event)) {
            switch(engine.event.type) {
                case SDL_QUIT: { engine.is_running = false; break; }
                case SDL_KEYDOWN: {
                    /* Close on Escape Key */
                    // To do: make it toggleable
                    if(engine.event.key.keysym.sym == SDLK_ESCAPE) { 
                        engine.is_running = false; break;
                    }
                }
            }
        }
        
        /* Get and set current and key states*/
        memcpy(engine.prev_keys, engine.curr_keys, sizeof(uint8_t)*SDL_NUM_SCANCODES);
        memcpy(engine.curr_keys, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

        /* Calculate FPS */
        engine.fps_avg = engine.frame_count/fps_timer.GetTime(&fps_timer);
        if(engine.fps_avg > 20000) { engine.fps_avg = 0.0f; }

        /* Process Scene(s) and GameObject(s) */
        int index = engine.scene_count-1;        /* Current Scene index */
        DE_GameScene *scene = engine.scenes[index];  /* Current scene */
        /* First frame of the scene. Same as at_beginning for scene */
        if(scene->is_first_frame == true) {
            scene->AtFirstFrame();
            scene->is_first_frame = false;

            /* First frame of objects */
            for(int i=0; i<scene->object_count; i++) {
                DE_GameObject *obj = scene->objects[i];
                obj->AtFirstFrame(obj);
            }
        }

        /* at_beginning of objects */
        for(int i=0; i<scene->object_count; i++) {
            DE_GameObject *obj = scene->objects[i];
            if(obj->is_beginning) {
                obj->AtBeginning(obj);
                obj->is_beginning = false;
            }
        }

        /* at_step of scenes and objects */
        scene->AtStep();
        for(int i=0; i<scene->object_count; i++) {
            DE_GameObject *obj = scene->objects[i];
            obj->AtStep(obj);
        }

        
        switch(engine.background.type) {
            case 0: DE_Renderer_ClearColor(engine.background.color); break;
            case 1: {
                DE_Rect rect = {engine.camera.x, engine.camera.y, engine.win_mode.x, engine.win_mode.y};
                DE_Renderer_Clear();
                DE_Renderer_TextureBlit(rect, 0, 0, engine.background.texture); 
                break;
            }
        }

        /* at_render of scenes and objects */
        scene->AtRender();
        for(int i=0; i<scene->object_count; i++) {
            DE_GameObject *obj = scene->objects[i];
            obj->AtRender(obj);
        }
        
#ifdef DECCAN_RENDERER_SDL
        SDL_RenderPresent(engine.renderer);
#else
        SDL_GL_SwapWindow(engine.window);
#endif

        /* Prevent mouse wheel scroll input spam */
        engine.event.wheel.x = 0;
        engine.event.wheel.y = 0;

        /* Increment the frame counter */
        engine.frame_count++;
        /* Current ticks per frame i.e delta time */
        engine.delta_time = frm_timer.GetTimeMS(&frm_timer);  

        /* Limit FPS */
        if(!engine.vsync_enabled && engine.fps_req > 0.0f) {
            float ticks_per_frame = 1000/engine.fps_req;  /* Required ticks per frame */
            if(engine.delta_time < ticks_per_frame) {
                DE_Clock_Delay((int)(ticks_per_frame - engine.delta_time));
            }
        }
    }
    
    /* at_end of scenes and objects */
    DE_GameScene *scene = engine.scenes[engine.scene_count-1];
    scene->AtEnd();
    for(int i=0; i<scene->object_count; i++) {
        DE_GameObject *obj = scene->objects[i];
        obj->AtEnd(obj);
        DE_msg_free(&obj->msg);
    }
    
    DE_msg_free(&engine.msg);
    DE_Core_Quit();
}

/* Core Settings Setters */
void DE_Core_SetTitle(const char *name) {
    SDL_SetWindowTitle(engine.window, name);
}

void DE_Core_SetMode(DE_Vector2i mode) {
    if(engine.is_fullscreen) {
        SDL_DisplayMode disp = {SDL_PIXELFORMAT_UNKNOWN, mode.x, mode.y, 0, 0};
        if(SDL_SetWindowDisplayMode(engine.window, &disp) > 0) {
            DE_report("Cannot set fullscreen window mode: %s", SDL_GetError());
        }
        SDL_MaximizeWindow(engine.window);
    }
    else { SDL_SetWindowSize(engine.window, mode.x, mode.y); }
    engine.win_mode = mode;
}

void DE_Core_SetFullscreen() {
    SDL_SetWindowFullscreen(engine.window, engine.is_fullscreen ? 0 : 1);
    engine.is_fullscreen = !engine.is_fullscreen;
}

void DE_Core_SetVsyncStatus(bool vsync) {
    // ??: Adaptive vsync
    if(SDL_GL_SetSwapInterval(vsync ? -1 : 0) == -1) {
        DE_report("VSync is not supported: %s", SDL_GetError());
    }

    int status = SDL_GL_GetSwapInterval();
    if(status == 0) { engine.vsync_enabled = false; }
    else { engine.vsync_enabled = true; }
}

void DE_Core_SetFramerateLimit(float fps){
    engine.fps_req = fps;
}

/* Core Settings Getters */
const char *DE_Core_GetTitle() {
    return SDL_GetWindowTitle(engine.window);
}

DE_Vector2i DE_Core_GetMode() {
    return engine.win_mode;
}

bool DE_Core_GetFullscreenStatus() {
    return engine.is_fullscreen;
}

bool DE_Core_GetVsyncStatus() {
    return engine.vsync_enabled;
}

float DE_Core_GetFramerateLimit() {
    return engine.fps_req;
}

float DE_Core_GetAverageFramerate() {
    return engine.fps_avg;
}

int32_t DE_Core_GetTotalFrameCount() {
    return engine.frame_count;
}

float DE_Core_GetDeltaTime() {
    return engine.delta_time;
}

void DE_Core_SendMessage(const char *msg) {
    DE_msg_send(&engine.msg, msg);
}

bool DE_Core_ReceiveMessage(const char *msg) {
    return DE_msg_receive(&engine.msg, msg);
}

void DE_error(const char *str, ...) {
    printf("Fatal Error: ");
    
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    
    printf("\n");
    exit(-1);
}

void DE_report(const char *str, ...) {
#ifdef DECCAN_REPORTS_ENABLED
    va_list args;
    
    va_start(args, str);
    vfprintf(engine.logfile, str, args);
    va_end(args);
    
    fprintf(engine.logfile, "\n");
#endif
}