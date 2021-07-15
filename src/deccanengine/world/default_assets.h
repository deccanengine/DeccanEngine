/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <deccanengine/config.h>
#include <deccanengine/core/asset/asset_manager.h>

////////////////////////////////////////////////////////////////////////////////
// Default Asset Manager
////////////////////////////////////////////////////////////////////////////////

deccan_asset_manager_t make_default_asset_manager(void);
void load_default_assets(void);
