/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

int core_init(deccan_core_desc_t *settings);
void core_quit(void);
void core_update(float fpsAverage, float deltaTime);

SDL_Window *core_get_window(void);
deccan_core_desc_t *core_get_settings(void);
