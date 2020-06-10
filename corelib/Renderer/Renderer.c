/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Renderer.h"
#include "Camera.h"
#include "../Core.h"

static struct {
#ifdef DECCAN_RENDERER_SDL
    SDL_Renderer *renderer;
#endif
    RawTexture *target;

    struct {
        int type; 
        union {
            SpriteAsset *texture;
            Color color;
        };
    } background;

} Renderer_Info = {0};

SDL_Renderer *Renderer_GetRenderer() {
    return Renderer_Info.renderer;
}

void Renderer_Init(SDL_Window *window) {
    int render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    if((Renderer_Info.renderer = SDL_CreateRenderer(window, -1, render_flags)) == NULL) {
        DE_ERROR("Could not create renderer: %s", SDL_GetError());
    }

    Renderer_Info.target = SDL_GetRenderTarget(Renderer_Info.renderer);
}

void Renderer_Quit() {
    SDL_DestroyRenderer(Renderer_Info.renderer);
}

void Renderer_Present() {
    SDL_RenderPresent(Renderer_Info.renderer);
}

void Renderer_Background() {
    if(Renderer_Info.background.type == 0) {
        Renderer_ClearColor(Renderer_Info.background.color); 
    }
    else {
        Renderer_Clear(); // Removing it produces artifacts 

        Vector2i mode = Core_GetMode();
        Vector2f camera = Camera_GetPosition();
            
        Rect rect = {
            camera.x, 
            camera.y, 
            mode.x, 
            mode.y
        };

        Sprite_Blit(rect, 0, 0, Renderer_Info.background.texture); 
    }
}

/* Setters */

void Renderer_Clear() {
    Color blank = {
        0, 0, 0, 0
    };

    Renderer_ClearColor(blank);
}

void Renderer_ClearColor(Color color) {
    Renderer_SetColor(color);
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderClear(Renderer_Info.renderer);
#else

#endif
}

void Renderer_SetBackgroundColor(Color color) {
    Renderer_Info.background.type = 0;
    Renderer_Info.background.color = color;
}

void Renderer_SetBackgroundTexture(SpriteAsset *texture) {
    Renderer_Info.background.type = 1;
    Renderer_Info.background.texture = texture;
}

void Renderer_SetTarget(SpriteAsset *target) { 
    RawTexture *texture;
    
    if(texture == NULL) { 
        texture = Renderer_Info.target; 
    }
    else {
        texture = target->texture[0];
    }

#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderTarget(Renderer_Info.renderer, texture) != 0) {
        DE_REPORT("Cannot set render target: %s", SDL_GetError());
    }
#else

#endif
}

void Renderer_SetColor(Color color) {
#ifdef DECCAN_RENDERER_SDL
    SDL_SetRenderDrawColor(Renderer_Info.renderer, color.r, color.g, color.b, color.a);
#else

#endif
}

void Renderer_SetPixelSize(Vector2f size) {
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderSetScale(Renderer_Info.renderer, size.x, size.y);
#else

#endif
}

void Renderer_SetBlendMode(int blend_mode) {
#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderDrawBlendMode(Renderer_Info.renderer, blend_mode) != 0) {
        DE_REPORT("Cannot set blend mode: %s", SDL_GetError());
    }
#else

#endif
}

/* Getters */

Color Renderer_GetBackgroundColor() {
    Color color = {
        0, 0, 0, 0
    };

    if(Renderer_Info.background.type == 0) { 
        color = Renderer_Info.background.color; 
    }

    return color;
}

SpriteAsset *Renderer_GetBackgroundTexture() {
    SpriteAsset *texture = NULL;

    if(Renderer_Info.background.type == 1) { 
        texture = Renderer_Info.background.texture; 
    }

    return texture;
}

SpriteAsset *Renderer_GetTarget() {
    SpriteAsset *target = DE_NEW(SpriteAsset, 1);
    target->name = DE_NEWSTRING("DE_Renderer_Target");

#ifdef DECCAN_RENDERER_SDL
    target->texture[0] = SDL_GetRenderTarget(Renderer_Info.renderer);
    if(target->texture == NULL) {
        DE_ERROR("Render target is NULL");
    }
#else

#endif
    return target;
}

Color Renderer_GetColor() {
    Color color = {
        0, 0, 0, 0
    };
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawColor(Renderer_Info.renderer, &color.r, &color.g, &color.b, &color.a);
#else

#endif
    return color;
}

Vector2f Renderer_GetPixelSize() {
    Vector2f size = {
        0.0f, 0.0f
    };
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderGetScale(Renderer_Info.renderer, &size.x, &size.y);
#else

#endif
    return size;
}

BlendMode Renderer_GetBlendMode() {
    SDL_BlendMode blend = SDL_BLENDMODE_NONE;
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawBlendMode(Renderer_Info.renderer, &blend);
#else

#endif
    return blend;
} 