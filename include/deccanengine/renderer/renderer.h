/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "framebuffer.h"

////////////////////////////////////////////////////////////////////////////////
// Renderer
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_renderer_pre_init(void);
DE_API void deccan_renderer_create(SDL_Window *window);
DE_API void deccan_renderer_destroy(void);
DE_API void deccan_renderer_draw(void);

////////////////////////////////////////////////////////////////////////////////
// Getters/setters
////////////////////////////////////////////////////////////////////////////////

DE_API SDL_GLContext deccan_renderer_get_context(void);
DE_API void deccan_renderer_set_viewport(vec2s viewport);
DE_API void deccan_renderer_set_clear_color(vec4s color);
DE_API void deccan_renderer_set_framebuffer(deccan_framebuffer_t *fb);
DE_API vec2s deccan_renderer_get_viewport(void);
DE_API vec4s deccan_renderer_get_clear_color(void);
DE_API deccan_framebuffer_t *deccan_renderer_get_framebuffer(void);
