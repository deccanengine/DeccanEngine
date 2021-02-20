/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
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

#include <depends/flecs/flecs.c>
#include <depends/log.c/src/log.c>

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

#ifdef DE_DEBUG
    FILE *logfile;
#endif
} Core_Info = {
    .isRunning = true,
    .isSettingsDirty = true,
};

/* Core */
int DE_CoreInit(DeccanSettings *settings) {
    int flags = SDL_INIT_VIDEO;
    if(SDL_Init(flags) != 0) {
        DE_FATAL("Could not initialize SDL2: %s", SDL_GetError());
    }

    if(TTF_Init() != 0) {
        DE_FATAL("Could not initialize SDL2_ttf: %s", TTF_GetError());
    }

    Core_Info.settings = *settings;

    /* Create window */
    SDL_WindowFlags window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;

    if(settings->fullscreen) { window_flags |= SDL_WINDOW_FULLSCREEN; }
    if(settings->resizable ) { window_flags |= SDL_WINDOW_RESIZABLE;  }

    if((Core_Info.window = SDL_CreateWindow(Core_Info.settings.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        Core_Info.settings.resolution[0], Core_Info.settings.resolution[1], window_flags)) == NULL) {
        DE_FATAL("Could not create window: %s", SDL_GetError());
    }

#ifdef DE_DEBUG
    /* Open the log file */
    Core_Info.logfile = fopen("report.log", "w");
    if(Core_Info.logfile == NULL) {
        DE_ERROR("Could not create/open log file");
    }

    log_add_fp(Core_Info.logfile, 0);
#endif

    DE_InputInit();
    DE_VarInit(&Core_Info.vars);

    return 1;
}

void DE_CoreQuit() {
#ifdef DE_DEBUG
    fclose(Core_Info.logfile);
#endif
    DE_VarQuit(&Core_Info.vars);
    SDL_DestroyWindow(Core_Info.window);

    TTF_Quit();
    SDL_Quit();
}

void DE_CoreUpdate(float fpsAverage, float deltaTime) {
    /* Handle some events */
    SDL_Event *event = DE_InputGetEventHandler();

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
                DE_WARN("Cannot set fullscreen window mode: %s", SDL_GetError());
            }

            SDL_MaximizeWindow(Core_Info.window);
        }
        else {
            SDL_SetWindowFullscreen(Core_Info.window, false);
            SDL_SetWindowSize(Core_Info.window, Core_Info.settings.resolution[0], Core_Info.settings.resolution[1]);
        }

    	// Issue: Not working in some Windows environment
    	if(SDL_GL_SetSwapInterval(Core_Info.settings.vsync ? 1 : 0) == -1) {
    		DE_WARN("VSync is not supported: %s", SDL_GetError());
    	}

        Core_Info.isSettingsDirty = false;
    }

    /* Update the input key states */
    DE_InputUpdate();

    Core_Info.fpsAverage = fpsAverage;
    Core_Info.deltaTime  = deltaTime;
}

/* Core Settings Setters */
void DE_CoreSetTitle(const char *name) {
    DE_Free(Core_Info.settings.title);
    Core_Info.settings.title = DE_StringNew(name);
    Core_Info.isSettingsDirty = true;
}

void DE_CoreSetResolution(vec2 resolution) {
    glm_vec2_copy(resolution, Core_Info.settings.resolution);
    Core_Info.isSettingsDirty = true;
}

void DE_CoreToogleFullscreen() {
    Core_Info.settings.fullscreen = !Core_Info.settings.fullscreen;
    Core_Info.isSettingsDirty = true;
}

void DE_CoreToogleVsync(bool vsync) {
    Core_Info.settings.vsync = vsync;
    Core_Info.isSettingsDirty = true;
}

void DE_CoreSetFramerateLimit(float fps){
    Core_Info.settings.fps = fps;
}

/* Core Settings Getters */
const char *DE_CoreGetTitle() {
    return Core_Info.settings.title;
}

void DE_CoreGetResolution(vec2 res) {
    glm_vec2_copy(Core_Info.settings.resolution, res);
}

bool DE_CoreIsFullscreened() {
    return Core_Info.settings.fullscreen;
}

bool DE_CoreIsVsyncEnabled() {
    return Core_Info.settings.vsync;
}

bool DE_CoreIsResizable() {
    return Core_Info.settings.resizable;
}

bool DE_CoreIsRunning() {
    return Core_Info.isRunning;
}

float DE_CoreGetFramerateLimit() {
    return Core_Info.settings.fps;
}

float DE_CoreGetAverageFramerate() {
    return Core_Info.fpsAverage;
}

float DE_CoreGetDeltaTime() {
    return Core_Info.deltaTime;
}

SDL_Window *DE_CoreGetWindowHandle() {
    return Core_Info.window;
}

DeccanVarManager *DE_CoreGetVarManager() {
    return &Core_Info.vars;
}

DeccanSettings *DE_CoreGetSettings() {
    return &Core_Info.settings;
}
