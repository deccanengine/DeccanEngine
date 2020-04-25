/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "draw.h"

#define DWC_FUNC void f(SDL_Renderer *renderer, Deccan_Vector2i camera)
#define DWC_FUNCREF f

void DE_draw_with_color(void (*DE_dwc_drawcall)(SDL_Renderer *renderer, Deccan_Vector2i camera), Deccan_Color color) {
    _priv_Renderer_set_color(color);
    Deccan_Info *engine = Deccan_Core.get_global_engine(); 
    DE_dwc_drawcall(engine->renderer, engine->camera);
}

void _priv_Renderer_draw_point(Deccan_Vector2i pos, Deccan_Color color) {
    DE_draw_with_color(({
        DWC_FUNC {
            SDL_RenderDrawPoint(renderer, pos.x - camera.x, pos.y - camera.y);
        } DWC_FUNCREF;
    }), color);
}

void _priv_Renderer_draw_line(Deccan_Vector2i start, Deccan_Vector2i end, Deccan_Color color) {
    DE_draw_with_color(({
        DWC_FUNC { 
            SDL_RenderDrawLine(renderer, start.x - camera.x, start.y - camera.y, end.x - camera.x, end.y - camera.y);
        } DWC_FUNCREF;
    }), color);
}

void _priv_Renderer_draw_rect(Deccan_Rect rect, Deccan_Color color) {
    DE_draw_with_color(({
        DWC_FUNC { 
            SDL_Rect sr = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
            SDL_RenderDrawRect(renderer, &sr);
        } DWC_FUNCREF;
    }), color);
}

void _priv_Renderer_draw_filled_rect(Deccan_Rect rect, Deccan_Color color) {
    DE_draw_with_color(({
        DWC_FUNC { 
            SDL_Rect sr = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
            SDL_RenderFillRect(renderer, &sr);
        } DWC_FUNCREF;
    }), color); 
}

void _priv_Renderer_draw_circle(Deccan_Circle circle, Deccan_Color color) {
    if(!circle.radius) { return; }

    DE_draw_with_color(({
        DWC_FUNC {
            int x = circle.x - camera.x;
            int y = circle.y - camera.y;
        
            int x0 = 0;
            int y0 = circle.radius;
            int d = 3 - 2 * circle.radius;
        
            void _draw_point(int32_t x, int32_t y) {
                SDL_RenderDrawPoint(renderer, x, y);
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
        } DWC_FUNCREF;
    }), color);    
}

void _priv_Renderer_draw_filled_circle(Deccan_Circle circle, Deccan_Color color) {
    if(!circle.radius) { return; }

    DE_draw_with_color(({
        DWC_FUNC {
            int x = circle.x - camera.x;
            int y = circle.y - camera.y;
        
            int x0 = 0;
            int y0 = circle.radius;
            int d = 3 - 2 * circle.radius;
        
            void _draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
                SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
            }

            while (y0 >= x0) {
                _draw_line(x - x0, y - y0, x + x0, y - y0);
			    _draw_line(x - y0, y - x0, x + y0, y - x0);
			    _draw_line(x - x0, y + y0, x + x0, y + y0);
			    _draw_line(x - y0, y + x0, x + y0, y + x0);
                if (d < 0) d += 4 * x0++ + 6;
                else d += 4 * (x0++ - y0--) + 10;
            }
        } DWC_FUNCREF;
    }), color);    
}