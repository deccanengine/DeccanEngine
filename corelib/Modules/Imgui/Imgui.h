#pragma once

#define SOKOL_IMGUI_NO_SOKOL_APP
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <depends/deimgui/cimgui.h>
#include <depends/deimgui/imgui_impl_sdl.h>
#include <depends/sokol/util/sokol_imgui.h>

void DE_ImguiInit(void);
void DE_ImguiQuit(void);
void DE_ImguiBeginRender(void);
void DE_ImguiEndRender(void);
