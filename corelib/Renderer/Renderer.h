/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

/////////////////////////////////////////////////
// Renderer
////////////////////////////////////////////////

DE_API void DE_RendererPreInit(void);
DE_API void DE_RendererCreate(SDL_Window *window);
DE_API void DE_RendererDestroy(void);
DE_API void DE_RendererDraw(void);

/////////////////////////////////////////////////
// Getters/setters
////////////////////////////////////////////////

DE_API SDL_GLContext DE_RendererGetContext(void);
DE_API void DE_RendererSetViewport(vec2s viewport);
DE_API void DE_RendererSetClearColor(vec4s color);
DE_API vec2s DE_RendererGetViewport(void);
DE_API vec4s DE_RendererGetClearColor(void);
