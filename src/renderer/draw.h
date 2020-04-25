/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "color.h"
#include "renderer.h"
#include "../physics/shape.h"
#include "../utils/vector.h"

void _priv_Renderer_draw_point(Deccan_Vector2i pos, Deccan_Color color);
void _priv_Renderer_draw_point2(int32_t x, int32_t y, Deccan_Color color);
void _priv_Renderer_draw_line(Deccan_Vector2i start, Deccan_Vector2i end, Deccan_Color color);
void _priv_Renderer_draw_line2(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Deccan_Color color);
void _priv_Renderer_draw_rect(Deccan_Rect rect, Deccan_Color color);
void _priv_Renderer_draw_filled_rect(Deccan_Rect rect, Deccan_Color color);
void _priv_Renderer_draw_circle(Deccan_Circle circle, Deccan_Color color);
void _priv_Renderer_draw_filled_circle(Deccan_Circle circle, Deccan_Color color);