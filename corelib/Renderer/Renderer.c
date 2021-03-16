/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Renderer.h"

DE_PRIV struct {
    SDL_GLContext glcontext;
    SDL_Window *window;

    sg_desc desc;

    vec2s viewport;
    vec4s clear_color;
} RendererInfo = {
    .glcontext = NULL,
    .window = NULL,

    .desc = {0},
};

DE_IMPL void DE_RendererPreInit(void) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

DE_IMPL void DE_RendererCreate(SDL_Window *window) {
    RendererInfo.window = window;
    RendererInfo.glcontext = SDL_GL_CreateContext(window);
    if (!RendererInfo.glcontext) {
        printf("Cannot create GL context: %s\n", SDL_GetError());
    }

    if (!gladLoadGL()) {
        printf("Couldn't load GLAD without context\n");
    }

    sg_setup(&RendererInfo.desc);
}

DE_IMPL void DE_RendererDestroy(void) {
    sg_shutdown();

    if (RendererInfo.glcontext != NULL)
        SDL_GL_DeleteContext(RendererInfo.glcontext);
}

DE_IMPL void DE_RendererDraw(void) {
    sg_commit();

    SDL_GL_SwapWindow(RendererInfo.window);
}

DE_IMPL SDL_GLContext DE_RendererGetContext(void) {
    return RendererInfo.glcontext;
}

DE_IMPL void DE_RendererSetViewport(vec2s viewport) {
    RendererInfo.viewport = viewport;
};

DE_IMPL void DE_RendererSetClearColor(vec4s color) {
    RendererInfo.clear_color = color;
}

DE_IMPL vec2s DE_RendererGetViewport(void) {
    return RendererInfo.viewport;
}

DE_IMPL vec4s DE_RendererGetClearColor(void) {
    return RendererInfo.clear_color;
}
