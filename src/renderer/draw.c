/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "draw.h"

#define DE_DRAW_BEGIN                           \
DE_Info *engine = DE_Core_get_global_engine();  \
DE_Color def = DE_Renderer_get_color();         \
SDL_BlendMode blend;                            \
DE_Renderer_set_color(color);                   \
SDL_GetRenderDrawBlendMode(engine->renderer, &blend);

#define DE_DRAW_END                             \
DE_Renderer_set_color(def);                     \
SDL_SetRenderDrawBlendMode(engine->renderer, blend);

void DE_Renderer_draw_point(DE_Vector2f pos, DE_Color color) {
    DE_DRAW_BEGIN;
    SDL_RenderDrawPoint(engine->renderer, pos.x - engine->camera.x, pos.y - engine->camera.y);
    DE_DRAW_END;
}

void DE_Renderer_draw_line(DE_Vector2f start, DE_Vector2f end, DE_Color color) {
    DE_DRAW_BEGIN;
    SDL_RenderDrawLine(engine->renderer, start.x - engine->camera.x, start.y - engine->camera.y, end.x - engine->camera.x, end.y - engine->camera.y);
    DE_DRAW_END;
}

void DE_Renderer_draw_rect(DE_Rect rect, DE_Color color) {
    DE_DRAW_BEGIN;
    SDL_Rect sr = {rect.x - engine->camera.x, rect.y - engine->camera.y, rect.w, rect.h};
    SDL_RenderDrawRect(engine->renderer, &sr);
    DE_DRAW_END;
}

void DE_Renderer_draw_rect_ext(DE_Rect rect, DE_Color color, float angle) {
    /*
    DE_draw_with_target(({
        DWT_FUNC{
            DE_draw_with_color(({
                DWC_FUNC { 
                    SDL_Rect sr = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
                    SDL_RenderDrawRect(renderer, &sr);
                } DWC_FUNCREF;
            }), color);
        } DWT_FUNCREF;
    }), angle, NULL, 0);
    */
}

void DE_Renderer_draw_filled_rect(DE_Rect rect, DE_Color color) {
    DE_DRAW_BEGIN;
    SDL_Rect sr = {rect.x - engine->camera.x, rect.y - engine->camera.y, rect.w, rect.h};
    SDL_RenderFillRect(engine->renderer, &sr);
    DE_DRAW_END;
}

void DE_Renderer_draw_circle(DE_Circle circle, DE_Color color) {
    if(!circle.radius) { return; }

    DE_DRAW_BEGIN;
    int x = circle.x - engine->camera.x;
    int y = circle.y - engine->camera.y;
        
    int x0 = 0;
    int y0 = circle.radius;
    int d = 3 - 2 * circle.radius;
        
    void _draw_point(int32_t x, int32_t y) {
        SDL_RenderDrawPoint(engine->renderer, x, y);
    }

    while (y0 >= x0) {
        _draw_point(x + x0, y - y0);
        _draw_point(x + y0, y - x0);
        _draw_point(x + y0, y + x0);
        _draw_point(x + x0, y + y0);
        _draw_point(x - x0, y + y0);
        _draw_point(x - y0, y + x0);
        _draw_point(x - y0, y - x0);
        _draw_point(x - x0, y - y0);
        if (d < 0) d += 4 * x0++ + 6;
        else d += 4 * (x0++ - y0--) + 10;
    }
    DE_DRAW_END;   
}

void DE_Renderer_draw_filled_circle(DE_Circle circle, DE_Color color) {
    if(!circle.radius) { return; }

    DE_DRAW_BEGIN;
    int x = circle.x - engine->camera.x;
    int y = circle.y - engine->camera.y;
        
    int x0 = 0;
    int y0 = circle.radius;
    int d = 3 - 2 * circle.radius;
        
    void _draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
        SDL_RenderDrawLine(engine->renderer, x1, y1, x2, y2);
    }

    while (y0 >= x0) {
        _draw_line(x - x0, y - y0, x + x0, y - y0);
		_draw_line(x - y0, y - x0, x + y0, y - x0);
		_draw_line(x - x0, y + y0, x + x0, y + y0);
		_draw_line(x - y0, y + x0, x + y0, y + x0);
        if (d < 0) d += 4 * x0++ + 6;
        else d += 4 * (x0++ - y0--) + 10;
    }
    DE_DRAW_END;    
}