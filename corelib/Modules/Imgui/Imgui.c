#include "../../Config.h"
#define SOKOL_GLCORE33
#define SOKOL_IMGUI_IMPL
#include "Imgui.h"
#include "../../Core/Core.h"
#include "../../Renderer/Renderer.h"

DE_PRIV struct {
    simgui_desc_t context;
} ImguiInfo = {0};

void DE_ImguiInit(void) {
   igCreateContext(NULL);
   ImGui_ImplSDL2_InitForOpenGL(DE_CoreGetWindow(), DE_RendererGetContext());
   simgui_setup(&ImguiInfo.context);
}

void DE_ImguiQuit(void) {
    igDestroyContext(NULL);
    simgui_shutdown();
}

void DE_ImguiBeginRender(void) {
    vec2s viewport;
    DE_CoreGetResolution(viewport.raw);

    ImGui_ImplSDL2_NewFrame(DE_CoreGetWindow());
    simgui_new_frame(viewport.x, viewport.y, 1.0f);
}

void DE_ImguiEndRender(void) {
    igRender();
    simgui_render();
}
