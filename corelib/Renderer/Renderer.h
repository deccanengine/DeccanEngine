#pragma once
#include "../Config.h"

void DE_RendererPreInit();
void DE_RendererCreate(SDL_Window *window);
void DE_RendererDestroy();
SDL_GLContext DE_RendererGetContext();
void DE_RendererDraw();

void DE_RendererSetViewport(vec2s viewport);
void DE_RendererSetClearColor(vec4s color);
vec2s DE_RendererGetViewport();
vec4s DE_RendererGetClearColor();
