/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

#ifdef DECCAN_RENDERER_SDL
    static SDL_Renderer *_renderer_renderer;
#endif

static RawTexture *_renderer_target;

struct {
    int type; 
    union {
        RawTexture *texture;
        Color color;
    };
} _renderer_background;

SDL_Renderer *Renderer_GetRenderer() {
    return _renderer_renderer;
}

void Renderer_Init(SDL_Window *window) {
    int render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    if((_renderer_renderer = SDL_CreateRenderer(window, -1, render_flags)) == NULL) {
        DE_error("Could not create renderer: %s", SDL_GetError());
    }

    _renderer_target = SDL_GetRenderTarget(_renderer_renderer);
}

void Renderer_Quit() {
    SDL_DestroyRenderer(_renderer_renderer);
}

void Renderer_Present() {
    SDL_RenderPresent(_renderer_renderer);
}

void Renderer_Background() {
    GameInfo *engine = Core_GetGlobalInfo();
    switch(_renderer_background.type) {
        case 0: {
            Renderer_ClearColor(_renderer_background.color); break;
        }
        case 1: {
            Renderer_Clear();
            Vector2i mode = Core_GetMode();
            Rect rect = {engine->camera.x, engine->camera.y, mode.x, mode.y};
            Renderer_TextureBlit(rect, 0, 0, _renderer_background.texture); 
            break;
        }
    }
}

/* Setters */

void Renderer_Clear() {
    Color blank = {0, 0, 0, 0};
    Renderer_ClearColor(blank);
}

void Renderer_ClearColor(Color color) {
    Renderer_SetColor(color);
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderClear(_renderer_renderer);
#else

#endif
}

void Renderer_SetBackgroundColor(Color color) {
    _renderer_background.type = 0;
    _renderer_background.color = color;
}

void Renderer_SetBackgroundTexture(RawTexture *texture) {
    _renderer_background.type = 1;
    _renderer_background.texture = texture;
}

void Renderer_SetTarget(RawTexture *target) { 
    if(target == NULL) { target = _renderer_target; }

#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderTarget(_renderer_renderer, target) != 0) {
        DE_report("Cannot set render target: %s", SDL_GetError());
    }
#else

#endif
}

void Renderer_SetColor(Color color) {
#ifdef DECCAN_RENDERER_SDL
    SDL_SetRenderDrawColor(_renderer_renderer, color.r, color.g, color.b, color.a);
#else

#endif
}

void Renderer_SetPixelSize(Vector2f size) {
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderSetScale(_renderer_renderer, size.x, size.y);
#else

#endif
}

void Renderer_SetBlendMode(int blend_mode) {
#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderDrawBlendMode(_renderer_renderer, blend_mode) != 0) {
        DE_report("Cannot set blend mode: %s", SDL_GetError());
    }
#else

#endif
}

/* Getters */

Color Renderer_GetBackgroundColor() {
    Color color = {0, 0, 0, 0};
    if(_renderer_background.type == 0) { 
        color = _renderer_background.color; 
    }
    return color;
}

RawTexture *Renderer_GetBackgroundTexture() {
    RawTexture *texture = NULL;
    if(_renderer_background.type == 1) { 
        texture = _renderer_background.texture; 
    }
    return texture;
}

RawTexture *Renderer_GetTarget() {
    RawTexture *target;
#ifdef DECCAN_RENDERER_SDL
    target = SDL_GetRenderTarget(_renderer_renderer);
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
    SDL_GetRenderDrawColor(_renderer_renderer, &color.r, &color.g, &color.b, &color.a);
#else

#endif
    return color;
}

Vector2f Renderer_GetPixelSize() {
    Vector2f size = {0.0f, 0.0f};
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderGetScale(_renderer_renderer, &size.x, &size.y);
#else

#endif
    return size;
}

BlendMode Renderer_GetBlendMode() {
    SDL_BlendMode blend = SDL_BLENDMODE_NONE;
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawBlendMode(_renderer_renderer, &blend);
#else

#endif
    return blend;
} 