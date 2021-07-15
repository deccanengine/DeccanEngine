/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/renderer/renderer.h>

DE_PRIV struct {
    SDL_GLContext glcontext;
    SDL_Window *window;
    deccan_framebuffer_t *fb;

    sg_desc desc;

    vec2s viewport;
    vec4s clear_color;
} renderer_info = {
    .glcontext = NULL,
    .window = NULL,
    .fb = NULL,

    .desc = {0},
};

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_renderer_pre_init(void) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_renderer_create(SDL_Window *window) {
    renderer_info.window = window;
    renderer_info.glcontext = SDL_GL_CreateContext(window);
    if (!renderer_info.glcontext) {
        printf("Cannot create GL context: %s\n", SDL_GetError());
    }

    if (!gladLoadGL()) {
        printf("Couldn't load GLAD without context\n");
    }

    renderer_info.desc.context = (sg_context_desc){
        .color_format = SG_PIXELFORMAT_RGBA8,
        .depth_format = SG_PIXELFORMAT_DEPTH,
        .sample_count = 4,
    };

    sg_setup(&renderer_info.desc);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_renderer_destroy(void) {
    sg_shutdown();

    if (renderer_info.glcontext != NULL)
        SDL_GL_DeleteContext(renderer_info.glcontext);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_renderer_draw(void) {
    sg_commit();

    SDL_GL_SwapWindow(renderer_info.window);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL SDL_GLContext deccan_renderer_get_context(void) {
    return renderer_info.glcontext;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_renderer_set_viewport(vec2s viewport) {
    renderer_info.viewport = viewport;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_renderer_set_clear_color(vec4s color) {
    renderer_info.clear_color = color;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_renderer_set_framebuffer(deccan_framebuffer_t *fb) {
    renderer_info.fb = fb;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL vec2s deccan_renderer_get_viewport(void) {
    return renderer_info.viewport;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL vec4s deccan_renderer_get_clear_color(void) {
    return renderer_info.clear_color;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_framebuffer_t *deccan_renderer_get_framebuffer(void) {
    return renderer_info.fb;
}
