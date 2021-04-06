/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "Config.h"

#include "Core/Core.h"
#include "Core/SDLHelper.h"
#include "Core/FileSys.h"
#include "Core/Variable.h"
#include "Core/Array.h"
#include "Core/Utils.h"
#include "Core/Timer.h"
#include "Core/Asset/AssetManager.h"
#include "Core/Asset/AssetDescriptor.h"
#include "Core/Input/Input.h"
#include "Core/Input/InputCodes.h"
#include "Core/Module/Module.h"

#include "Modules/Physics/Collision.h"
#include "Modules/Imgui/Imgui.h"

#include "Scene/Object.h"
#include "Scene/Scene.h"

#include "Renderer/Color.h"
#include "Renderer/GenericPipeline.h"
#include "Renderer/PrimitiveGeometry.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderTypes.h"
#include "Renderer/Texture.h"

#include "World/Camera.h"
#include "World/Flecs.h"
#include "World/Components.h"

DE_API bool DE_AppInit(DeccanSettings *settings);
DE_API void DE_AppUpdate(void);
DE_API void DE_AppQuit(void);
