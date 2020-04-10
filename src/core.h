#pragma once

#include "config.h"
#include "input.h"
#include "utils/log.h"
#include "utils/timer.h"

typedef struct {
    char *name;

    bool is_paused;
    bool is_first_frame;

    state_func_ptr(at_begining);
    state_func_ptr(at_step);
    state_func_ptr(at_end);
} deccan_Scene;

typedef struct deccan_Info {
    /* Core engine */
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;

    /* Settings */
    float required_fps;

    /* Input system */
    SDL_Event event;
    uint8_t *key_states;

    /* Scene manager */
    deccan_Scene **scenes;

    /* Asset manager */
    struct {
        char *key;
        SDL_Texture *value;
    } *textures;
} deccan_Info;

void deccan_set_global_engine(deccan_Info *engine);
deccan_Info *deccan_get_global_engine();

int  deccan_init(const char *title, int32_t width, int32_t height);
void deccan_quit();
void deccan_run(float required_fps);

deccan_Scene *deccan_new_scene(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae));
void deccan_add_scene(deccan_Scene *scene, bool is_replacing);
void deccan_remove_scene();

deccan_Scene *deccan_current_scene();
void deccan_pause_scene(bool pause);
bool deccan_is_scene_paused();
