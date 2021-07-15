/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "config.h"

#include "core/core.h"
#include "core/file_sys.h"
#include "core/utils.h"
#include "core/timer.h"
#include "core/maths.h"
#include "core/asset/asset_manager.h"
#include "core/asset/asset_descriptor.h"
#include "core/input/input.h"
#include "core/input/input_codes.h"

#include "physics/physics.h"
#include "physics/collision.h"

#include "renderer/color.h"
#include "renderer/generic_pipeline.h"
#include "renderer/renderer.h"
#include "renderer/render_types.h"
#include "renderer/texture.h"

#include "world/object.h"
#include "world/scene.h"
#include "world/scene_layer.h"
#include "world/world.h"
#include "world/camera.h"
#include "world/flecs.h"
#include "world/components/transform.h"
#include "world/components/drawable_geometry.h"
#include "world/components/drawable_sprite.h"
#include "world/components/rigid_body.h"
#include "world/components/collider.h"
#include "world/components/legacy_collider.h"

DE_API bool deccan_app_init(deccan_core_desc_t *settings);
DE_API void deccan_app_update(void);
DE_API void deccan_app_quit(void);
