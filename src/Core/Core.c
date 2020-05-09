/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#define STB_DS_IMPLEMENTATION
#include <Deccan/Core.h>
#include <Deccan/Renderer.h>

static GameInfo engine;

#ifdef DECCAN_RENDERER_SDL
    static SDL_Window *_core_window;
#else

#endif

int _core_gl_major;
int _core_gl_minor;
bool _core_is_running;

Vector2i _core_win_mode;
bool _core_is_fullscreen;
bool _core_vsync_enabled;
int32_t _core_frame_count;
float _core_fps_req;
float _core_fps_avg;
float _core_delta_time;

msgbuf _core_msg;

#ifdef DECCAN_REPORTS_ENABLED
    FILE *_core_logfile;
#endif

/* Core */
void Core_SetGlobalInfo(GameInfo *info) {
    engine = *info;
}

GameInfo *Core_GetGlobalInfo() {
    return &engine;
}

int Core_Init(const char *title, Vector2i mode) {
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
    if((_core_window = SDL_CreateWindow(title, 0, 0, mode.x, mode.y, window_flags)) == NULL) {
        DE_error("Could not create window: %s", SDL_GetError());
    }

    /* Set the renderer to OpenGL */
    if(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl") != SDL_TRUE) {
        DE_error("OpenGL cannot be enabled");
    }

    /* Create renderer */
    Renderer_Init(_core_window);
#else
    
#endif
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &_core_gl_major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &_core_gl_minor);
    if(_core_gl_major < 2 || (_core_gl_major == 2 && _core_gl_minor < 1)) {
        DE_error("OpenGL 2.1 support needed at minimum. Consider upgrading your hardware.");
    }

    /* Open the log file */
    _core_logfile = fopen("report.log", "w");
    if(_core_logfile == NULL) {
        DE_error("Could not create/open log file");
    }

    _core_is_running = true;

    _core_win_mode = mode;
    _core_vsync_enabled = false;
    _core_fps_req = 60.0f;      /* Fallback FPS limit if vsync is disabled somwhere and new limit is not set */

    engine.scenes = NULL;
    engine.scene_count = 0;

    engine.camera_bounds = (PosRect){-1, -1, -1, -1};

    msg_init(&_core_msg, DECCAN_MSG_COUNT, DECCAN_MSG_LENGTH);

    memcpy(engine.prev_keys, "\0", sizeof(uint8_t)*SDL_NUM_SCANCODES);
    memcpy(engine.curr_keys, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

    return 1;
}

void Core_Quit() {
    fclose(_core_logfile);
    stbds_arrfree(engine.scenes);
#ifdef DECCAN_RENDERER_SDL
    Renderer_Quit();
    SDL_DestroyWindow(_core_window);    
#else
    
#endif
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Core_Run(float fps) {
    Timer fps_timer = Clock_NewTimer();
    Timer frm_timer = Clock_NewTimer();

    fps_timer.Start(&fps_timer);    /* To calculate FPS */

    /* If no FPS limit is set then enable VSync*/
    if(fps <= 0.0f) { Core_SetVsyncStatus(true); }
    else { Core_SetVsyncStatus(false); }
    
    /* Set FPS limit if VSync is not enabled */
    /* There is no gurantee than VSync is enabled by set_vsync_status().
     * Hence, it is separated. 
     */
    if(!_core_vsync_enabled) { _core_fps_req = fps; }

    while(_core_is_running) {
        frm_timer.Start(&frm_timer);

        /* Handle some events */
        if(SDL_PollEvent(&engine.event)) {
            switch(engine.event.type) {
                case SDL_QUIT: { _core_is_running = false; break; }
                case SDL_KEYDOWN: {
                    /* Close on Escape Key */
                    // To do: make it toggleable
                    if(engine.event.key.keysym.sym == SDLK_ESCAPE) { 
                        _core_is_running = false; break;
                    }
                }
            }
        }
        
        /* Get and set current and key states*/
        memcpy(engine.prev_keys, engine.curr_keys, sizeof(uint8_t)*SDL_NUM_SCANCODES);
        memcpy(engine.curr_keys, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);

        /* Calculate FPS */
        _core_fps_avg = _core_frame_count/fps_timer.GetTime(&fps_timer);
        if(_core_fps_avg > 20000) { _core_fps_avg = 0.0f; }

        /* Process Scene(s) and GameObject(s) */
        int index = engine.scene_count-1;        /* Current Scene index */
        GameScene *scene = engine.scenes[index];  /* Current scene */
        /* First frame of the scene. Same as at_beginning for scene */
        if(scene->is_first_frame == true) {
            scene->AtFirstFrame();
            scene->is_first_frame = false;

            /* First frame of objects */
            for(int i=0; i<scene->object_count; i++) {
                GameObject *obj = scene->objects[i];
                obj->AtFirstFrame(obj);
            }
        }

        /* at_beginning of objects */
        for(int i=0; i<scene->object_count; i++) {
            GameObject *obj = scene->objects[i];
            if(obj->is_beginning) {
                obj->AtBeginning(obj);
                obj->is_beginning = false;
            }
        }

        /* at_step of scenes and objects */
        scene->AtStep();
        for(int i=0; i<scene->object_count; i++) {
            GameObject *obj = scene->objects[i];
            obj->AtStep(obj);
        }

        
        Renderer_Background();

        /* at_render of scenes and objects */
        scene->AtRender();
        for(int i=0; i<scene->object_count; i++) {
            GameObject *obj = scene->objects[i];
            obj->AtRender(obj);
        }
        
#ifdef DECCAN_RENDERER_SDL
        Renderer_Present();
#else

#endif

        /* Prevent mouse wheel scroll input spam */
        engine.event.wheel.x = 0;
        engine.event.wheel.y = 0;

        /* Increment the frame counter */
        _core_frame_count++;
        /* Current ticks per frame i.e delta time */
        _core_delta_time = frm_timer.GetTimeMS(&frm_timer);  

        /* Limit FPS */
        if(!_core_vsync_enabled && _core_fps_req > 0.0f) {
            float ticks_per_frame = 1000/_core_fps_req;  /* Required ticks per frame */
            if(_core_delta_time < ticks_per_frame) {
                Clock_Delay((int)(ticks_per_frame - _core_delta_time));
            }
        }
    }
    
    /* at_end of scenes and objects */
    GameScene *scene = engine.scenes[engine.scene_count-1];
    scene->AtEnd();
    for(int i=0; i<scene->object_count; i++) {
        GameObject *obj = scene->objects[i];
        obj->AtEnd(obj);
        msg_free(&obj->msg);
    }
    
    msg_free(&_core_msg);
    Core_Quit();
}

/* Core Settings Setters */
void Core_SetTitle(const char *name) {
    SDL_SetWindowTitle(_core_window, name);
}

void Core_SetMode(Vector2i mode) {
    if(_core_is_fullscreen) {
        SDL_DisplayMode disp = {SDL_PIXELFORMAT_UNKNOWN, mode.x, mode.y, 0, 0};
        if(SDL_SetWindowDisplayMode(_core_window, &disp) > 0) {
            DE_report("Cannot set fullscreen window mode: %s", SDL_GetError());
        }
        SDL_MaximizeWindow(_core_window);
    }
    else { SDL_SetWindowSize(_core_window, mode.x, mode.y); }
    _core_win_mode = mode;
}

void Core_SetFullscreen() {
    SDL_SetWindowFullscreen(_core_window, _core_is_fullscreen ? 0 : 1);
    _core_is_fullscreen = !_core_is_fullscreen;
}

void Core_SetVsyncStatus(bool vsync) {
    // ??: Adaptive vsync
    if(SDL_GL_SetSwapInterval(vsync ? -1 : 0) == -1) {
        DE_report("VSync is not supported: %s", SDL_GetError());
    }

    int status = SDL_GL_GetSwapInterval();
    if(status == 0) { _core_vsync_enabled = false; }
    else { _core_vsync_enabled = true; }
}

void Core_SetFramerateLimit(float fps){
    _core_fps_req = fps;
}

/* Core Settings Getters */
const char *Core_GetTitle() {
    return SDL_GetWindowTitle(_core_window);
}

Vector2i Core_GetMode() {
    return _core_win_mode;
}

bool Core_GetFullscreenStatus() {
    return _core_is_fullscreen;
}

bool Core_GetVsyncStatus() {
    return _core_vsync_enabled;
}

float Core_GetFramerateLimit() {
    return _core_fps_req;
}

float Core_GetAverageFramerate() {
    return _core_fps_avg;
}

int32_t Core_GetTotalFrameCount() {
    return _core_frame_count;
}

float Core_GetDeltaTime() {
    return _core_delta_time;
}

void Core_SendMessage(const char *msg) {
    msg_send(&_core_msg, msg);
}

bool Core_ReceiveMessage(const char *msg) {
    return msg_receive(&_core_msg, msg);
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
    vfprintf(_core_logfile, str, args);
    va_end(args);
    
    fprintf(_core_logfile, "\n");
#endif
}