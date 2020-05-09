/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

/* Setters */

void Renderer_Clear() {
    Color blank = {0, 0, 0, 0};
    Renderer_ClearColor(blank);
}

void Renderer_ClearColor(Color color) {
    Renderer_SetColor(color);
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderClear(Core_GetGlobalInfo()->renderer);
#else

#endif
}

void Renderer_SetBackgroundColor(Color color) {
    GameInfo *engine = Core_GetGlobalInfo();
    engine->background.type = 0;
    engine->background.color = color;
}

void Renderer_SetBackgroundTexture(RawTexture *texture) {
    GameInfo *engine = Core_GetGlobalInfo();
    engine->background.type = 1;
    engine->background.texture = texture;
}

void Renderer_SetTarget(RawTexture *target) {
    GameInfo *engine = Core_GetGlobalInfo(); 
    if(target == NULL) { target = engine->target; }

#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderTarget(engine->renderer, target) != 0) {
        DE_report("Cannot set render target: %s", SDL_GetError());
    }
#else

#endif
}

void Renderer_SetColor(Color color) {
#ifdef DECCAN_RENDERER_SDL
    SDL_SetRenderDrawColor(Core_GetGlobalInfo()->renderer, color.r, color.g, color.b, color.a);
#else

#endif
}

void Renderer_SetPixelSize(Vector2f size) {
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderSetScale(Core_GetGlobalInfo()->renderer, size.x, size.y);
#else

#endif
}

void Renderer_SetBlendMode(int blend_mode) {
#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderDrawBlendMode(Core_GetGlobalInfo()->renderer, blend_mode) != 0) {
        DE_report("Cannot set blend mode: %s", SDL_GetError());
    }
#else

#endif
}

/* Getters */

Color Renderer_GetBackgroundColor() {
    Color color = {0, 0, 0, 0};
    GameInfo *engine = Core_GetGlobalInfo();
    if(engine->background.type == 0) { 
        color = engine->background.color; 
    }
    return color;
}

RawTexture *Renderer_GetBackgroundTexture() {
    RawTexture *texture = NULL;
    GameInfo *engine = Core_GetGlobalInfo();
    if(engine->background.type == 1) { 
        texture = engine->background.texture; 
    }
    return texture;
}

RawTexture *Renderer_GetTarget() {
    RawTexture *target;
#ifdef DECCAN_RENDERER_SDL
    target = SDL_GetRenderTarget(Core_GetGlobalInfo()->renderer);
    if(target == NULL) {
        DE_error("Render target is NULL");
    }
#else

#endif
    return target;
}

Color Renderer_GetColor() {
    Color color = {0, 0, 0, 0};
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawColor(Core_GetGlobalInfo()->renderer, &color.r, &color.g, &color.b, &color.a);
#else

#endif
    return color;
}

Vector2f Renderer_GetPixelSize() {
    Vector2f size = {0.0f, 0.0f};
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderGetScale(Core_GetGlobalInfo()->renderer, &size.x, &size.y);
#else

#endif
    return size;
}

BlendMode Renderer_GetBlendMode() {
    SDL_BlendMode blend = SDL_BLENDMODE_NONE;
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawBlendMode(Core_GetGlobalInfo()->renderer, &blend);
#else

#endif
    return blend;
} 