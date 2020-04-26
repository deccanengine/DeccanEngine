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

void DE_Renderer_draw_point(DE_Vector2i pos, DE_Color color);
void DE_Renderer_draw_point2(int32_t x, int32_t y, DE_Color color);
void DE_Renderer_draw_line(DE_Vector2i start, DE_Vector2i end, DE_Color color);
void DE_Renderer_draw_line2(int32_t x1, int32_t y1, int32_t x2, int32_t y2, DE_Color color);
void DE_Renderer_draw_rect(DE_Rect rect, DE_Color color);
void DE_Renderer_draw_filled_rect(DE_Rect rect, DE_Color color);
void DE_Renderer_draw_circle(DE_Circle circle, DE_Color color);
void DE_Renderer_draw_filled_circle(DE_Circle circle, DE_Color color);