/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM

#define STB_DS_IMPLEMENTATION

#include "Core.h"
#include "Input/Input.h"

static struct {
    SDL_Window *window;

    bool isRunning;
    bool isSettingsDirty;

    float fpsAverage;
    float deltaTime;

    DeccanSettings settings;
    DeccanVarManager vars;

#ifdef DECCAN_REPORTS_ENABLED
    FILE *logfile;
#endif
} Core_Info = {
    .isRunning = true,
    .isSettingsDirty = true,
};

/* Core */
int Core_Init(DeccanSettings *settings) {
    int flags = SDL_INIT_VIDEO;
    if(SDL_Init(flags) != 0) {
        DE_ERROR("Could not initialize SDL2: %s", SDL_GetError());
    }

    if(TTF_Init() != 0) {
        DE_ERROR("Could not initialize SDL2_ttf: %s", TTF_GetError());
    }

    Core_Info.settings = *settings;

    /* Create window */
    SDL_WindowFlags window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;

    if(settings->fullscreen) { window_flags |= SDL_WINDOW_FULLSCREEN; }
    if(settings->resizable ) { window_flags |= SDL_WINDOW_RESIZABLE;  }

    if((Core_Info.window = SDL_CreateWindow(Core_Info.settings.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        Core_Info.settings.resolution[0], Core_Info.settings.resolution[1], window_flags)) == NULL) {
        DE_ERROR("Could not create window: %s", SDL_GetError());
    }

#ifdef DECCAN_REPORTS_ENABLED
    /* Open the log file */
    Core_Info.logfile = fopen("report.log", "w");
    if(Core_Info.logfile == NULL) {
        DE_ERROR("Could not create/open log file");
    }
#endif

    Input_Init();
    DE_Var_Init(&Core_Info.vars);

    return 1;
}

void Core_Quit() {
#ifdef DECCAN_REPORTS_ENABLED
    fclose(Core_Info.logfile);
#endif
    //Msg_Free(&Core_Info.msg); -- HERE

    SDL_DestroyWindow(Core_Info.window);

    TTF_Quit();
    SDL_Quit();
}

void DE_Core_Update(float fpsAverage, float deltaTime) {
    /* Handle some events */
    SDL_Event *event = Input_GetEventHandler();

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

    if(Core_Info.isSettingsDirty) {
        SDL_SetWindowTitle(Core_Info.window, Core_Info.settings.title);

        if(Core_Info.settings.fullscreen) {
            SDL_SetWindowFullscreen(Core_Info.window, true);

            SDL_DisplayMode disp = {SDL_PIXELFORMAT_UNKNOWN,
                Core_Info.settings.resolution[0], Core_Info.settings.resolution[1], 0, 0};

            if(SDL_SetWindowDisplayMode(Core_Info.window, &disp) > 0) {
                DE_REPORT("Cannot set fullscreen window mode: %s", SDL_GetError());
            }

            SDL_MaximizeWindow(Core_Info.window);
        }
        else {
            SDL_SetWindowFullscreen(Core_Info.window, false);
            SDL_SetWindowSize(Core_Info.window, Core_Info.settings.resolution[0], Core_Info.settings.resolution[1]);
        }

    	// Issue: Not working in some Windows environment
    	if(SDL_GL_SetSwapInterval(Core_Info.settings.vsync ? 1 : 0) == -1) {
    		DE_REPORT("VSync is not supported: %s", SDL_GetError());
    	}

        Core_Info.isSettingsDirty = false;
    }

    /* Update the input key states */
    Input_Update();

    Core_Info.fpsAverage = fpsAverage;
    Core_Info.deltaTime  = deltaTime;
}

/* Core Settings Setters */
void Core_SetTitle(const char *name) {
    DE_Mem_Delete(Core_Info.settings.title);
    Core_Info.settings.title = DE_String_New(name);
    Core_Info.isSettingsDirty = true;
}

void Core_SetResolution(vec2 resolution) {
    glm_vec2_copy(resolution, Core_Info.settings.resolution);
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

void Core_GetResolution(vec2 res) {
    glm_vec2_copy(Core_Info.settings.resolution, res);
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

bool Core_IsRunning() {
    return Core_Info.isRunning;
}

float Core_GetFramerateLimit() {
    return Core_Info.settings.fps;
}

float Core_GetAverageFramerate() {
    return Core_Info.fpsAverage;
}

float Core_GetDeltaTime() {
    return Core_Info.deltaTime;
}

SDL_Window *DE_Core_GetWindowHandle() {
    return Core_Info.window;
}

DeccanVarManager *DE_Core_GetVarManager() {
    return &Core_Info.vars;
}

DeccanSettings *DE_Core_GetSettings() {
    return &Core_Info.settings;
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
