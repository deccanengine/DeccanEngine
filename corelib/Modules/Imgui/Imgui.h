/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../../Core/Module/Module.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <depends/deimgui/cimgui.h>

/////////////////////////////////////////////////
// Constructor/destructor
////////////////////////////////////////////////

DE_API void DE_ImguiInit(void);
DE_API void DE_ImguiQuit(void);

/////////////////////////////////////////////////
// Renderer
////////////////////////////////////////////////

DE_API void DE_ImguiBeginRender(void);
DE_API void DE_ImguiEndRender(void);

/////////////////////////////////////////////////
// Module
////////////////////////////////////////////////

DE_API DeccanModule *DE_ImguiModule(void);

