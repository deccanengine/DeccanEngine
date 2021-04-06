/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Imgui.h"
#include "../../Core/Core.h"
#include "../../Renderer/Renderer.h"

#define SOKOL_GLCORE33
#define SOKOL_IMGUI_IMPL
#define SOKOL_IMGUI_NO_SOKOL_APP
#include <depends/deimgui/imgui_impl_sdl.h>
#include <depends/sokol/util/sokol_imgui.h>

DE_PRIV struct { simgui_desc_t context; } ImguiInfo = {0};

DE_IMPL void DE_ImguiInit(void) {
    igCreateContext(NULL);
    ImGui_ImplSDL2_InitForOpenGL(DE_CoreGetWindow(), DE_RendererGetContext());
    simgui_setup(&ImguiInfo.context);
}

DE_IMPL void DE_ImguiQuit(void) {
    igDestroyContext(NULL);
    simgui_shutdown();
}

DE_IMPL void DE_ImguiBeginRender(void) {
    vec2s viewport;
    DE_CoreGetResolution(viewport.raw);

    ImGui_ImplSDL2_NewFrame(DE_CoreGetWindow());
    simgui_new_frame(viewport.x, viewport.y, DE_CoreGetDeltaTime());
}

DE_IMPL void DE_ImguiEndRender(void) {
    igRender();
    simgui_render();
}

/////////////////////////////////////////////////
// Module
////////////////////////////////////////////////

DE_API DeccanModule *DE_ImguiModule(void) {
    DeccanModule *imgui = DE_ModuleCreate("imgui");
    imgui->AtBeginning = DE_ImguiInit;
    imgui->AtStep = DE_ImguiBeginRender;
    imgui->AtPostStep = DE_ImguiEndRender;
    imgui->AtEnd = DE_ImguiQuit;
    return imgui;
}

