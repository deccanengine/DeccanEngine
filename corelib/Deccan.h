/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "Config.h"

#include "Core/Core.h"
#include "Core/Asset.h"
#include "Core/Variable.h"
#include "Core/Memory.h"
#include "Core/Timer.h"
#include "Core/Input/Input.h"
#include "Core/Input/InputCodes.h"

#include "Asset/Importer.h"
#include "Asset/SpriteAsset.h"
#include "Asset/FontAsset.h"

#include "Modules/Modules.h"

#include "Scene/Object.h"
#include "Scene/Scene.h"
#include "Scene/Flecs.h"
#include "Scene/ComponentList.h"

#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer/TextRendering.h"

bool DE_App_Init(DeccanSettings *settings);
void DE_App_Update();
void DE_App_Quit();
