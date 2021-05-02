/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Imgui.h"
#include "../Core/Core.h"
#include "../Renderer/Renderer.h"

#define SOKOL_GLCORE33
#define SOKOL_IMGUI_IMPL
#define SOKOL_IMGUI_NO_SOKOL_APP
#include <depends/deimgui/imgui_impl_sdl.h>
#include <depends/sokol/util/sokol_imgui.h>

DE_PRIV struct { 
    simgui_desc_t context; 
} imgui_info = {0};

DE_IMPL void deccan_imgui_init(void) {
    simgui_setup(&imgui_info.context);   
    ImGui_ImplSDL2_InitForOpenGL(deccan_core_get_window(), deccan_renderer_get_context());
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_imgui_quit(void) {
    simgui_shutdown();
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_imgui_begin_render(void) {
    vec2s viewport;
    deccan_core_get_resolution(viewport.raw);

    ImGui_ImplSDL2_NewFrame(deccan_core_get_window());
    simgui_new_frame(viewport.x, viewport.y, deccan_core_get_delta_time());
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_imgui_end_render(void) {
    igRender();
    simgui_render();
}

/////////////////////////////////////////////////////////////////////////////////
// Module
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_module_t *deccan_imgui_module(void) {
    deccan_module_t *imgui = deccan_module_create("imgui");
    imgui->AtBeginning = deccan_imgui_init;
    imgui->AtStep = deccan_imgui_begin_render;
    imgui->AtPostStep = deccan_imgui_end_render;
    imgui->AtEnd = deccan_imgui_quit;
    return imgui;
}

