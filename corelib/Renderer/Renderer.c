/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "TextRendering.h"
#include "../Core/Core.h"

static struct {
#ifdef DECCAN_RENDERER_SDL
    SDL_Renderer *renderer;
#endif
    DeccanRawTexture *target;

    int glMajor;
    int glMinor;

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
    if(!window) return;

    /* GL Attributes: OpenGL 2.1 with hardware acceleration */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    /* Set the renderer to OpenGL */
    if(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl") != SDL_TRUE) {
        DE_ERROR("OpenGL cannot be enabled");
    }

    int render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    if((Renderer_Info.renderer = SDL_CreateRenderer(window, -1, render_flags)) == NULL) {
        DE_ERROR("Could not create renderer: %s", SDL_GetError());
    }

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &Renderer_Info.glMajor);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &Renderer_Info.glMinor);
    if(Renderer_Info.glMajor < 2 || (Renderer_Info.glMajor == 2 && Renderer_Info.glMinor < 1)) {
        DE_ERROR("OpenGL 2.1 support needed at minimum. Consider upgrading your hardware.");
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

        vec2 mode; Core_GetResolution(mode);
        vec2 camera; Camera_GetPosition(camera);

        vec4 rect = {
            camera[0],
            camera[1],
            mode[0],
            mode[1]
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
    DeccanRawTexture *texture;

    if(target == NULL) {
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

void Renderer_SetPixelSize(vec2 size) {
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderSetScale(Renderer_Info.renderer, size[0], size[1]);
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
    SpriteAsset *target = DE_Mem_New(sizeof(SpriteAsset), 1);
    target->name = DE_String_New("DE_Renderer_Target");

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

void Renderer_GetPixelSize(vec2 size) {
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderGetScale(Renderer_Info.renderer, &size[0], &size[1]);
#else

#endif
}

BlendMode Renderer_GetBlendMode() {
    SDL_BlendMode blend = SDL_BLENDMODE_NONE;
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawBlendMode(Renderer_Info.renderer, &blend);
#else

#endif
    return blend;
}
