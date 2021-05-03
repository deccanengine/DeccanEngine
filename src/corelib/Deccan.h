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
#include "Core/Utils.h"
#include "Core/Timer.h"
#include "Core/Asset/AssetManager.h"
#include "Core/Asset/AssetDescriptor.h"
#include "Core/Input/Input.h"
#include "Core/Input/InputCodes.h"
#include "Core/Module/Module.h"

#include "Physics/Collision.h"

#include "Imgui/Imgui.h"

#include "Renderer/Color.h"
#include "Renderer/GenericPipeline.h"
#include "Renderer/PrimitiveGeometry.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderTypes.h"
#include "Renderer/Texture.h"

#include "World/Object.h"
#include "World/Scene.h"
#include "World/Camera.h"
#include "World/Flecs.h"
#include "World/DefaultAssets.h"
#include "World/Components.h"
#include "World/Systems.h"
#include "World/Resources/Sprite.h"

DE_API bool deccan_app_init(deccan_settings_t *settings);
DE_API void deccan_app_update(void);
DE_API void deccan_app_quit(void);
