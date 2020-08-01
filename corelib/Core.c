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
#include "Scene/ECSystem.h"

static struct {
    SDL_Window *window;

    int glMajor;
    int glMinor;

    CoreSettings settings;

    bool isRunning;
    bool isSettingsDirty;
    
    int32_t frameCount;
    float fpsAverage;
    float deltaTime;

    MsgBuf msg;

#ifdef DECCAN_REPORTS_ENABLED
    FILE *logfile;
#endif
} Core_Info = {
    .isRunning = true,
    .isSettingsDirty = true,
    .frameCount = 0
};

/* Core */
int Core_Init(CoreSettings *settings) {
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

    Core_Info.settings = *settings;

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
    SDL_WindowFlags window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
    
    if(settings->fullscreen) { window_flags |= SDL_WINDOW_FULLSCREEN; }
    if(settings->resizable ) { window_flags |= SDL_WINDOW_RESIZABLE;  }
    
    if((Core_Info.window = SDL_CreateWindow(Core_Info.settings.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        Core_Info.settings.resolution.x, Core_Info.settings.resolution.y, window_flags)) == NULL) {
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

    Input_Init();
    Msg_Init(&Core_Info.msg, DECCAN_MSG_COUNT, DECCAN_MSG_LENGTH);

    return 1;
}

void Core_Quit() {
    ECSystem_FreeAllComponents();
    ECSystem_FreeAllSystems();

    Msg_Free(&Core_Info.msg);

    fclose(Core_Info.logfile);
    Scene_FreeAll();

    Renderer_Quit();
    SDL_DestroyWindow(Core_Info.window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void UpdateAll() {
    /* Process Scene(s) and GameObject(s) */
    GameScene *scene = Scene_CurrentScene();  /* Current scene */

    /* First frame of the scene. Same as at_beginning for scene */
    if(scene->is_first_frame == true) {
        scene->AtFirstFrame();
        scene->is_first_frame = false;

        /* First frame of objects */
        for(int i=0; i<stbds_arrlen(scene->objects); i++) {
            GameObject *obj = scene->objects[i];
            obj->AtFirstFrame(obj);
        }
    }

    /* AtStep of scenes and objects */
    scene->AtStep();
        
    for(int i=0; i<stbds_arrlen(scene->objects); i++) {
        Object_Update(scene->objects[i]);
    }

    /* Render the background before rendering anything */
    Renderer_Background();

    /* AtRender of scenes and objects */
    scene->AtRender();
        
    for(int i=0; i<stbds_arrlen(scene->objects); i++) {
        Object_Render(scene->objects[i]);
    }
}

void HandleSettings() {
    SDL_SetWindowTitle(Core_Info.window, Core_Info.settings.title);

    if(Core_Info.settings.fullscreen) {
        SDL_SetWindowFullscreen(Core_Info.window, true);

        SDL_DisplayMode disp = {SDL_PIXELFORMAT_UNKNOWN, 
            Core_Info.settings.resolution.x, Core_Info.settings.resolution.y, 0, 0};
        
        if(SDL_SetWindowDisplayMode(Core_Info.window, &disp) > 0) {
            DE_REPORT("Cannot set fullscreen window mode: %s", SDL_GetError());
        }
        
        SDL_MaximizeWindow(Core_Info.window);
    }
    else {
        SDL_SetWindowFullscreen(Core_Info.window, false);
        SDL_SetWindowSize(Core_Info.window, Core_Info.settings.resolution.x, Core_Info.settings.resolution.y); 
    }

    if(SDL_GL_SetSwapInterval(Core_Info.settings.vsync ? 1 : 0) == -1) {
        DE_REPORT("VSync is not supported: %s", SDL_GetError());
    }
}

void HandleEvents(SDL_Event *event) {
    /* Handle some events */
    if(SDL_PollEvent(event)) {
        switch(event->type) {
            /* Handle close event */
            case SDL_QUIT: { 
                Core_Info.isRunning = false; 
                break; 
            }

            /* Handle close on escape key event */
            case SDL_KEYDOWN: {
                /* Close on Escape Key */
                if(event->key.keysym.sym == SDLK_ESCAPE && 
                   Core_Info.settings.closeOnEscape) { 
                    Core_Info.isRunning = false; 
                    break;
                }
            }
        }
    }
}

void ProcessEnd() {
    /* at_end of scenes and objects */
    GameScene *scene = Scene_CurrentScene();

    scene->AtEnd();
    for(int i=0; i<stbds_arrlen(scene->objects); i++) {
        Object_End(scene->objects[i]);
        Object_DeleteObject(scene->objects[i]);
    }
}

void Core_Run() {
    Timer fpsTimer;
    Timer frmTimer;

    Clock_StartTimer(&fpsTimer);    /* To calculate FPS */

    SDL_Event *event = Input_GetEventHandler();

    while(Core_Info.isRunning) {
        Clock_StartTimer(&frmTimer);

        /* Handle all events */
        HandleEvents(event);

        if(Core_Info.isSettingsDirty) {
            HandleSettings();
            Core_Info.isSettingsDirty = false;
        }

        /* Calculate FPS */
        Core_Info.fpsAverage = Core_Info.frameCount / Clock_GetTime(&fpsTimer).seconds;
        if(Core_Info.fpsAverage > 20000) { 
            Core_Info.fpsAverage = 0.0f; 
        }

        /* Update the scene and all objects */
        UpdateAll();
        
        /* Render everything */
        Renderer_Present();

        /* Update the input key states */
        Input_Update();

        /* Increment the frame counter */
        Core_Info.frameCount++; 
        
        /* Current ticks per frame i.e delta time */
        Core_Info.deltaTime = Clock_GetTime(&frmTimer).milliseconds;  

        /* Limit FPS */
        if((!Core_Info.settings.vsync) && 
           (Core_Info.settings.fps > 20.0f)) {
            float ticksPerFrame = (1000.0f / Core_Info.settings.fps);  /* Required ticks per frame */
            if(Core_Info.deltaTime < ticksPerFrame) {
                Clock_Delay((int)(ticksPerFrame - Core_Info.deltaTime));
            }
        }
    }
    
    ProcessEnd();
    Core_Quit();
}

/* Core Settings Setters */
void Core_SetTitle(const char *name) {
    Core_Info.settings.title = DE_NEWSTRING(name);
    Core_Info.isSettingsDirty = true;
}

void Core_SetResolution(Vector2 resolution) {
    Core_Info.settings.resolution = resolution;
    Core_Info.isSettingsDirty = true;
}

void Core_ToogleFullscreen() {
    Core_Info.settings.fullscreen = !Core_Info.settings.fullscreen;
    Core_Info.isSettingsDirty = true;
}

void Core_ToogleVsync(bool vsync) {
    Core_Info.settings.vsync = vsync;
    Core_Info.isSettingsDirty = true;
}

void Core_SetFramerateLimit(float fps){
    Core_Info.settings.fps = fps;
}

/* Core Settings Getters */ 
const char *Core_GetTitle() {
    return Core_Info.settings.title;
}

Vector2 Core_GetResolution() {
    return Core_Info.settings.resolution;
}

bool Core_IsFullscreened() {
    return Core_Info.settings.fullscreen;
}

bool Core_IsVsyncEnabled() {
    return Core_Info.settings.vsync;
}

bool Core_IsResizable() {
    return Core_Info.settings.resizable;
}

float Core_GetFramerateLimit() {
    return Core_Info.settings.fps;
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