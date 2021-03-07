#include "Renderer.h"

static struct {
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

void DE_RendererPreInit() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void DE_RendererCreate(SDL_Window *window) {
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

void DE_RendererDestroy() {
    sg_shutdown();

    if (RendererInfo.glcontext != NULL)
        SDL_GL_DeleteContext(RendererInfo.glcontext);
}

void DE_RendererDraw() {
    sg_commit();

    SDL_GL_SwapWindow(RendererInfo.window);
}

void DE_RendererSetViewport(vec2s viewport) {
    RendererInfo.viewport = viewport;
};

void DE_RendererSetClearColor(vec4s color) {
    RendererInfo.clear_color = color;
}

vec2s DE_RendererGetViewport() {
    return RendererInfo.viewport;
}

vec4s DE_RendererGetClearColor() {
    return RendererInfo.clear_color;
}
