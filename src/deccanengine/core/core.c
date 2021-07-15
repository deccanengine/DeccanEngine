/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/core/core.h>
#include <deccanengine/core/input/input.h>
#include "core_internal.h"

DE_PRIV struct {
    SDL_Window *window;

    bool is_running;
    bool is_settings_dirty;

    float fps_average;
    float delta_time;
    uint32_t proc_start_time;

    deccan_core_desc_t settings;
#ifdef DE_DEBUG
    FILE *logfile;
#endif
} core_info = {
    .is_running = true,
    .is_settings_dirty = true,
};


////////////////////////////////////////////////////////////////////////////////
// Core functions
////////////////////////////////////////////////////////////////////////////////

int core_init(deccan_core_desc_t *settings) {
    core_info.settings = *settings;

    /* Create window */
    SDL_WindowFlags window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;

    if (settings->fullscreen) {
        window_flags |= SDL_WINDOW_FULLSCREEN;
    }
    if (settings->resizable) {
        window_flags |= SDL_WINDOW_RESIZABLE;
    }

    if ((core_info.window = SDL_CreateWindow(core_info.settings.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             core_info.settings.resolution.x, core_info.settings.resolution.y, window_flags)) == NULL) {
        DE_FATAL("Could not create window: %s", SDL_GetError());
    }

#ifdef DE_DEBUG
    /* Open the log file */
    core_info.logfile = fopen("report.log", "w");
    if (core_info.logfile == NULL) {
        DE_ERROR("Could not create/open log file");
    }

    log_add_fp(core_info.logfile, 0);
#endif

    core_info.proc_start_time = SDL_GetTicks();

    deccan_input_init();

    return 1;
}

////////////////////////////////////////////////////////////////////////////////

void core_quit(void) {
#ifdef DE_DEBUG
    fclose(core_info.logfile);
#endif
    SDL_DestroyWindow(core_info.window);

    /* TTF_Quit(); */
    SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////

void core_update(float fps_average, float delta_time) {
    /* Handle some events */
    SDL_Event *event = deccan_input_get_event_handler();

    if (SDL_PollEvent(event)) {
        switch (event->type) {
        /* Handle close event */
        case SDL_QUIT: {
            core_info.is_running = false;
            break;
        }

        /* Handle close on escape key event */
        case SDL_KEYDOWN: {
            /* Close on Escape Key */
            if (event->key.keysym.sym == SDLK_ESCAPE && core_info.settings.close_on_escape) {
                core_info.is_running = false;
                break;
            }
        }
        }
    }

    if (core_info.is_settings_dirty) {
        SDL_SetWindowTitle(core_info.window, core_info.settings.title);

        if (core_info.settings.fullscreen) {
            SDL_SetWindowFullscreen(core_info.window, true);

            SDL_DisplayMode disp = {
                SDL_PIXELFORMAT_UNKNOWN, core_info.settings.resolution.x, core_info.settings.resolution.y, 0, 0};

            if (SDL_SetWindowDisplayMode(core_info.window, &disp) > 0) {
                DE_WARN("Cannot set fullscreen window mode: %s", SDL_GetError());
            }

            SDL_MaximizeWindow(core_info.window);
        }
        else {
            SDL_SetWindowFullscreen(core_info.window, false);
            SDL_SetWindowSize(core_info.window, core_info.settings.resolution.x, core_info.settings.resolution.y);
        }

        // Issue: Not working in some Windows environment
        if (SDL_GL_SetSwapInterval(core_info.settings.vsync ? 1 : 0) == -1) {
            DE_WARN("VSync is not supported: %s", SDL_GetError());
        }

        core_info.is_settings_dirty = false;
    }

    /* Update the input key states */
    deccan_input_update();

    core_info.fps_average = fps_average;
    core_info.delta_time = delta_time;
}

////////////////////////////////////////////////////////////////////////////////

/* Core Settings Setters */
DE_IMPL void deccan_core_set_title(const char *name) {
    deccan_free(core_info.settings.title);
    core_info.settings.title = deccan_string_new(name);
    core_info.is_settings_dirty = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_core_set_resolution(vec2s resolution) {
    core_info.settings.resolution = resolution;
    core_info.is_settings_dirty = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_core_toogle_fullscreen(void) {
    core_info.settings.fullscreen = !core_info.settings.fullscreen;
    core_info.is_settings_dirty = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_core_toogle_vsync(bool vsync) {
    core_info.settings.vsync = vsync;
    core_info.is_settings_dirty = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_core_set_framerate_limit(float fps) {
    core_info.settings.fps = fps;
}

////////////////////////////////////////////////////////////////////////////////

/* Core Settings Getters */
DE_IMPL const char *deccan_core_get_title(void) {
    return core_info.settings.title;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL vec2s deccan_core_get_resolution(void) {
    return core_info.settings.resolution;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_core_is_fullscreened(void) {
    return core_info.settings.fullscreen;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_core_is_vsync_enabled(void) {
    return core_info.settings.vsync;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_core_is_resizable(void) {
    return core_info.settings.resizable;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_core_is_running(void) {
    return core_info.is_running;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL float deccan_core_get_framerate_limit(void) {
    return core_info.settings.fps;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL float deccan_core_get_average_framerate(void) {
    return core_info.fps_average;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL float deccan_core_get_delta_time(void) {
    return core_info.delta_time;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL uint32_t deccan_core_process_start_time(void) {
    return core_info.proc_start_time;
}

////////////////////////////////////////////////////////////////////////////////

SDL_Window *core_get_window(void) {
    return core_info.window;
}

////////////////////////////////////////////////////////////////////////////////

deccan_core_desc_t *core_get_settings(void) {
    return &core_info.settings;
}
