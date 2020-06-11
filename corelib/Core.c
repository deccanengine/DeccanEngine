/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#define STB_DS_IMPLEMENTATION
#include "Core.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"

static struct {
#ifdef DECCAN_RENDERER_SDL
    SDL_Window *window;
#endif

    int glMajor;
    int glMinor;

    Vector2 winMode;

    bool isRunning;
    bool isFullscreen;
    bool isVsyncEnabled;
    
    int32_t frameCount;
    float fpsRequired;
    float fpsAverage;
    float deltaTime;

    MsgBuf msg;

#ifdef DECCAN_REPORTS_ENABLED
    FILE *logfile;
#endif
} Core_Info = {
    .isRunning = true,
    .isFullscreen = false,
    .isVsyncEnabled = false,
    .fpsRequired = 60.0f,
    .frameCount = 0
};

/* Core */
int Core_Init(const char *title, Vector2 mode) {
    int flags = SDL_INIT_VIDEO;
    if(SDL_Init(flags) != 0) {
        DE_ERROR("Could not initialize SDL2: %s", SDL_GetError());
    }

    int image_flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if(!IMG_Init(image_flags) & !image_flags) {
        DE_ERROR("Could not initialize SDL2_image: %s", IMG_GetError());
    }

    if(TTF_Init() != 0) {
        DE_ERROR("Could not initialize SDL2_ttf: %s", TTF_GetError());
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
    if((Core_Info.window = SDL_CreateWindow(title, 0, 0, mode.x, mode.y, window_flags)) == NULL) {
        DE_ERROR("Could not create window: %s", SDL_GetError());
    }

    /* Set the renderer to OpenGL */
    if(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl") != SDL_TRUE) {
        DE_ERROR("OpenGL cannot be enabled");
    }

    /* Create renderer */
    Renderer_Init(Core_Info.window);
#else
    
#endif
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &Core_Info.glMajor);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &Core_Info.glMinor);
    if(Core_Info.glMajor < 2 || (Core_Info.glMajor == 2 && Core_Info.glMinor < 1)) {
        DE_ERROR("OpenGL 2.1 support needed at minimum. Consider upgrading your hardware.");
    }

    /* Open the log file */
    Core_Info.logfile = fopen("report.log", "w");
    if(Core_Info.logfile == NULL) {
        DE_ERROR("Could not create/open log file");
    }

    Core_Info.winMode = mode;

    Input_Init();
    Msg_Init(&Core_Info.msg, DECCAN_MSG_COUNT, DECCAN_MSG_LENGTH);

    return 1;
}

void Core_Quit() {
    fclose(Core_Info.logfile);
    Scene_FreeAll();

#ifdef DECCAN_RENDERER_SDL
    Renderer_Quit();
    SDL_DestroyWindow(Core_Info.window);    
#else
    
#endif
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Core_Run(float fps) {
    Timer fpsTimer;
    Timer frmTimer;

    Clock_StartTimer(&fpsTimer);    /* To calculate FPS */

    /* If no FPS limit is set then enable VSync*/
    if(fps <= 0.0f) 
         { Core_SetVsyncStatus(true);  }
    else { Core_SetVsyncStatus(false); }
    
    /* Set FPS limit if VSync is not enabled */
    if(!Core_Info.isVsyncEnabled) { 
        Core_Info.fpsRequired = fps; 
    }

    SDL_Event *event = Input_GetEventHandler();

    while(Core_Info.isRunning) {
        Clock_StartTimer(&frmTimer);

        /* Handle some events */
        if(SDL_PollEvent(event)) {
            switch(event->type) {
                case SDL_QUIT: { Core_Info.isRunning = false; break; }
                case SDL_KEYDOWN: {
                    /* Close on Escape Key */
                    // To do: make it toggleable
                    if(event->key.keysym.sym == SDLK_ESCAPE) { 
                        Core_Info.isRunning = false; break;
                    }
                }
            }
        }


        /* Calculate FPS */
        Core_Info.fpsAverage = Core_Info.frameCount / Clock_GetTime(&fpsTimer).seconds;
        if(Core_Info.fpsAverage > 20000) { 
            Core_Info.fpsAverage = 0.0f; 
        }

        /* Process Scene(s) and GameObject(s) */
        int index = Scene_GetSceneCount()-1;        /* Current Scene index */
        GameScene *scene = Scene_GetSceneArray()[index];  /* Current scene */

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

        /* AtBeginning of objects */
        for(int i=0; i<scene->object_count; i++) {
            GameObject *obj = scene->objects[i];
            if(obj->is_beginning) {
                obj->AtBeginning(obj);
                obj->is_beginning = false;
            }
        }

        /* AtStep of scenes and objects */
        scene->AtStep();
        for(int i=0; i<scene->object_count; i++) {
            GameObject *obj = scene->objects[i];
            if(!obj->is_beginning) {
                obj->AtStep(obj);
            }
        }

        /* Render the background before rendering anything */
        Renderer_Background();

        /* AtRender of scenes and objects */
        scene->AtRender();
        for(int i=0; i<scene->object_count; i++) {
            GameObject *obj = scene->objects[i];
            if(!obj->is_beginning) {
                obj->AtRender(obj);
            }
        }
        
#ifdef DECCAN_RENDERER_SDL
        Renderer_Present();
#else

#endif

        /* Update the input key states */
        Input_Update();

        Core_Info.frameCount++; /* Increment the frame counter */
        
        /* Current ticks per frame i.e delta time */
        Core_Info.deltaTime = Clock_GetTime(&frmTimer).milliseconds;  

        /* Limit FPS */
        if(!Core_Info.isVsyncEnabled && (Core_Info.fpsRequired > 0.0f)) {
            float ticksPerFrame = (1000.0f / Core_Info.fpsRequired);  /* Required ticks per frame */
            if(Core_Info.deltaTime < ticksPerFrame) {
                Clock_Delay((int)(ticksPerFrame - Core_Info.deltaTime));
            }
        }
    }
    
    /* at_end of scenes and objects */
    GameScene *scene = Scene_GetSceneArray()[Scene_GetSceneCount()-1];
    scene->AtEnd();
    for(int i=0; i<scene->object_count; i++) {
        GameObject *obj = scene->objects[i];
        obj->AtEnd(obj);
        Msg_Free(&obj->msg);
    }
    
    Msg_Free(&Core_Info.msg);
    Core_Quit();
}

/* Core Settings Setters */
void Core_SetTitle(const char *name) {
    SDL_SetWindowTitle(Core_Info.window, name);
}

void Core_SetMode(Vector2 mode) {
    if(Core_Info.isFullscreen) {
        SDL_DisplayMode disp = {SDL_PIXELFORMAT_UNKNOWN, mode.x, mode.y, 0, 0};
        
        if(SDL_SetWindowDisplayMode(Core_Info.window, &disp) > 0) {
            DE_REPORT("Cannot set fullscreen window mode: %s", SDL_GetError());
        }
        
        SDL_MaximizeWindow(Core_Info.window);
    }
    else { 
        SDL_SetWindowSize(Core_Info.window, mode.x, mode.y); 
    }
    Core_Info.winMode = mode;
}

void Core_SetFullscreen() {
    SDL_SetWindowFullscreen(Core_Info.window, Core_Info.isFullscreen ? 0 : 1);
    Core_Info.isFullscreen = !Core_Info.isFullscreen;
}

void Core_SetVsyncStatus(bool vsync) {
    // ??: Adaptive vsync
    if(SDL_GL_SetSwapInterval(vsync ? -1 : 0) == -1) {
        DE_REPORT("VSync is not supported: %s", SDL_GetError());
    }

    int status = SDL_GL_GetSwapInterval();
    if(status == 0) 
         { Core_Info.isVsyncEnabled = false; }
    else { Core_Info.isVsyncEnabled = true; }
}

void Core_SetFramerateLimit(float fps){
    Core_Info.fpsRequired = fps;
}

/* Core Settings Getters */
const char *Core_GetTitle() {
    return SDL_GetWindowTitle(Core_Info.window);
}

Vector2 Core_GetMode() {
    return Core_Info.winMode;
}

bool Core_GetFullscreenStatus() {
    return Core_Info.isFullscreen;
}

bool Core_GetVsyncStatus() {
    return Core_Info.isVsyncEnabled;
}

float Core_GetFramerateLimit() {
    return Core_Info.fpsRequired;
}

float Core_GetAverageFramerate() {
    return Core_Info.fpsAverage;
}

int32_t Core_GetTotalFrameCount() {
    return Core_Info.frameCount;
}

float Core_GetDeltaTime() {
    return Core_Info.deltaTime;
}

void Core_SendMessage(const char *msg) {
    Msg_Send(&Core_Info.msg, msg);
}

bool Core_ReceiveMessage(const char *msg) {
    return Msg_Receive(&Core_Info.msg, msg);
}

void DE_ERROR(const char *str, ...) {
    printf("Fatal Error: ");
    
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    
    printf("\n");
    exit(-1);
}

void DE_REPORT(const char *str, ...) {
#ifdef DECCAN_REPORTS_ENABLED
    va_list args;
    
    va_start(args, str);
    vfprintf(Core_Info.logfile, str, args);
    va_end(args);
    
    fprintf(Core_Info.logfile, "\n");
#endif
}