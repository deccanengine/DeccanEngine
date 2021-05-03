/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Deccan.h"

bool deccan_app_init(deccan_settings_t *settings) {
    deccan_sdl_init();

    deccan_renderer_pre_init();
    deccan_core_init(settings);
    deccan_renderer_create(deccan_core_get_window());

    deccan_scene_sys_create();

    deccan_generic_pipeline_create();

    return true;
}

void deccan_app_update(void) {
    deccan_timer_t fpsTimer;
    deccan_timer_t frmTimer;

    deccan_timer_start(&fpsTimer); /* To calculate FPS */

    int32_t frameCount;
    float fpsAverage = 0.0f;
    float deltaTime = 0.0f;

    deccan_settings_t *settings = deccan_core_get_settings();

    deccan_scene_make_changes();

    while (deccan_core_is_running()) {
        deccan_timer_start(&frmTimer);

        /* Calculate FPS */
        fpsAverage = frameCount / deccan_timer_get_time(&fpsTimer).seconds;
        if (fpsAverage > 20000) {
            fpsAverage = 0.0f;
        }

        deccan_core_update(fpsAverage, deltaTime);

        vec2s viewport;
        deccan_core_get_resolution(viewport.raw);
        deccan_renderer_set_viewport(viewport);

        /* Update and render the scene */
        deccan_generic_pipeline_begin(deccan_scene_get_camera());
        deccan_scene_update();
        deccan_generic_pipeline_end();

        /* Render everything */
        deccan_renderer_draw();

        /* Increment the frame counter */
        frameCount++;

        /* Current ticks per frame i.e delta time */
        deltaTime = deccan_timer_get_time(&frmTimer).milliseconds;

        /* Limit FPS */
        if ((!settings->vsync) && (settings->fps > 20.0f)) {
            float ticksPerFrame = (1000.0f / settings->fps); /* Required ticks per frame */
            if (deltaTime < ticksPerFrame) {
                deccan_clock_delay((int)(ticksPerFrame - deltaTime));
            }
        }

        /* Update delta time */
        deltaTime = deccan_timer_get_time(&frmTimer).milliseconds;
    }
}

void deccan_app_quit(void) {
    deccan_scene_quit();

    deccan_scene_free_all();

    deccan_generic_pipeline_destroy();
    deccan_renderer_destroy();

    deccan_core_quit();
}
