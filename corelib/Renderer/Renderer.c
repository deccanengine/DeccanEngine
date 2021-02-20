/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "TextRendering.h"
#include "../Core/Core.h"
#include "../Core/String.h"

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
            DeccanSpriteAsset *texture;
            DeccanColor color;
        };
    } background;

} Renderer_Info = {0};

SDL_Renderer *DE_RendererGetRenderer() {
    return Renderer_Info.renderer;
}

void DE_RendererInit(SDL_Window *window) {
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

void DE_RendererQuit() {
    SDL_DestroyRenderer(Renderer_Info.renderer);
}

void DE_RendererPresent() {
    SDL_RenderPresent(Renderer_Info.renderer);
}

void DE_RendererBackground() {
    if(Renderer_Info.background.type == 0) {
        DE_RendererClearColor(Renderer_Info.background.color);
    }
    else {
        DE_RendererClear(); // Removing it produces artifacts

        vec2 mode; DE_CoreGetResolution(mode);
        vec2 camera; DE_CameraGetPosition(camera);

        vec4 rect = {
            camera[0],
            camera[1],
            mode[0],
            mode[1]
        };

        DE_SpriteBlit(rect, 0, 0, Renderer_Info.background.texture);
    }
}

/* Setters */

void DE_RendererClear() {
    DeccanColor blank = {
        0, 0, 0, 0
    };

    DE_RendererClearColor(blank);
}

void DE_RendererClearColor(DeccanColor color) {
    DE_RendererSetColor(color);
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderClear(Renderer_Info.renderer);
#else

#endif
}

void DE_RendererSetBackgroundColor(DeccanColor color) {
    Renderer_Info.background.type = 0;
    Renderer_Info.background.color = color;
}

void DE_RendererSetBackgroundTexture(DeccanSpriteAsset *texture) {
    Renderer_Info.background.type = 1;
    Renderer_Info.background.texture = texture;
}

void DE_RendererSetTarget(DeccanSpriteAsset *target) {
    DeccanRawTexture *texture;

    if(target == NULL) {
        texture = Renderer_Info.target;
    }
    else {
        texture = target->texture[0];
    }

#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderTarget(Renderer_Info.renderer, texture) != 0) {
        DE_WARN("Cannot set render target: %s", SDL_GetError());
    }
#else

#endif
}

void DE_RendererSetColor(DeccanColor color) {
#ifdef DECCAN_RENDERER_SDL
    SDL_SetRenderDrawColor(Renderer_Info.renderer, color.r, color.g, color.b, color.a);
#else

#endif
}

void DE_RendererSetPixelSize(vec2 size) {
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderSetScale(Renderer_Info.renderer, size[0], size[1]);
#else

#endif
}

void DE_RendererSetBlendMode(int blend_mode) {
#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderDrawBlendMode(Renderer_Info.renderer, blend_mode) != 0) {
        DE_WARN("Cannot set blend mode: %s", SDL_GetError());
    }
#else

#endif
}

/* Getters */

DeccanColor DE_RendererGetBackgroundColor() {
    DeccanColor color = {
        0, 0, 0, 0
    };

    if(Renderer_Info.background.type == 0) {
        color = Renderer_Info.background.color;
    }

    return color;
}

DeccanSpriteAsset *DE_RendererGetBackgroundTexture() {
    DeccanSpriteAsset *texture = NULL;

    if(Renderer_Info.background.type == 1) {
        texture = Renderer_Info.background.texture;
    }

    return texture;
}

DeccanSpriteAsset *DE_RendererGetTarget() {
    DeccanSpriteAsset *target = DE_Alloc(sizeof(DeccanSpriteAsset), 1);
    target->name = DE_StringNew("DE_DE_RendererTarget");

#ifdef DECCAN_RENDERER_SDL
    target->texture[0] = SDL_GetRenderTarget(Renderer_Info.renderer);
    if(target->texture == NULL) {
        DE_ERROR("Render target is NULL");
    }
#else

#endif
    return target;
}

DeccanColor DE_RendererGetColor() {
    DeccanColor color = {
        0, 0, 0, 0
    };
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawColor(Renderer_Info.renderer, &color.r, &color.g, &color.b, &color.a);
#else

#endif
    return color;
}

void DE_RendererGetPixelSize(vec2 size) {
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderGetScale(Renderer_Info.renderer, &size[0], &size[1]);
#else

#endif
}

DeccanRenderBlendMode DE_RendererGetBlendMode() {
    SDL_BlendMode blend = SDL_BLENDMODE_NONE;
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawBlendMode(Renderer_Info.renderer, &blend);
#else

#endif
    return blend;
}
