/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "../core/core.h"
#include "color.h"

typedef struct {
    int32_t x, y, w, h;
} Deccan_Rect;

void _priv_Renderer_clear(Deccan_Color color);
void _priv_Renderer_set_color(Deccan_Color color);

void _priv_Renderer_draw_point(Deccan_Vector2i pos, Deccan_Color color);
void _priv_Renderer_draw_point2(int32_t x, int32_t y, Deccan_Color color);
void _priv_Renderer_draw_line(Deccan_Vector2i start, Deccan_Vector2i end, Deccan_Color color);
void _priv_Renderer_draw_line2(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Deccan_Color color);
void _priv_Renderer_draw_rect(Deccan_Rect rect, bool fill, Deccan_Color color);
void _priv_Renderer_draw_circle(Deccan_Vector3i circle, bool fill, Deccan_Color color);

typedef struct _priv_Renderer {
    void (*clear)(Deccan_Color color);
    void (*set_color)(Deccan_Color color);
    void (*draw_point)(Deccan_Vector2i pos, Deccan_Color color);
    void (*draw_point2)(int32_t x, int32_t y, Deccan_Color color);
    void (*draw_line)(Deccan_Vector2i start, Deccan_Vector2i end, Deccan_Color color);
    void (*draw_line2)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Deccan_Color color);
    void (*draw_rect)(Deccan_Rect rect, bool fill, Deccan_Color color);
    void (*draw_circle)(Deccan_Vector3i circle, bool fill, Deccan_Color color);
} _priv_Renderer;

static _priv_Renderer Deccan_Renderer = {
    _priv_Renderer_clear,
    _priv_Renderer_set_color,
    _priv_Renderer_draw_point,
    _priv_Renderer_draw_point2,
    _priv_Renderer_draw_line,
    _priv_Renderer_draw_line2,
    _priv_Renderer_draw_rect,
    _priv_Renderer_draw_circle
};