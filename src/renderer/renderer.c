/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "renderer.h"

void _priv_Renderer_clear(Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderClear(Deccan_Core.get_global_engine()->renderer);
}

void _priv_Renderer_set_color(Deccan_Color color) {
    SDL_SetRenderDrawColor(Deccan_Core.get_global_engine()->renderer, color.r, color.g, color.b, color.a);
}

void _priv_Renderer_draw_point(Deccan_Vector2i pos, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderDrawPoint(Deccan_Core.get_global_engine()->renderer, pos.x, pos.y);
}

void _priv_Renderer_draw_point2(int32_t x, int32_t y, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderDrawPoint(Deccan_Core.get_global_engine()->renderer, x, y);
}

void _priv_Renderer_draw_line(Deccan_Vector2i start, Deccan_Vector2i end, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderDrawLine(Deccan_Core.get_global_engine()->renderer, start.x, start.y, end.x, end.y);
}

void _priv_Renderer_draw_line2(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderDrawLine(Deccan_Core.get_global_engine()->renderer, x1, y1, x2, y2);
}

void _priv_Renderer_draw_rect(Deccan_Rect rect, bool fill, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    if(fill) { SDL_RenderFillRect(Deccan_Core.get_global_engine()->renderer, &(SDL_Rect){rect.x, rect.y, rect.w, rect.h}); }
    else { SDL_RenderDrawRect(Deccan_Core.get_global_engine()->renderer, &(SDL_Rect){rect.x, rect.y, rect.w, rect.h}); }
}

void _priv_Renderer_draw_circle(Deccan_Vector3i circle, bool fill, Deccan_Color color) {
    int x = circle.x;
    int y = circle.y;
    int radius = circle.z;
    
    int x0 = 0;
	int y0 = circle.z;
	int d = 3 - 2 * radius;
	//if (!radius) return false;

	while (y0 >= x0) {
        if(fill) {
            Deccan_Renderer.draw_line2(x - x0, y - y0, x + x0, y - y0, color);
			Deccan_Renderer.draw_line2(x - y0, y - x0, x + y0, y - x0, color);
			Deccan_Renderer.draw_line2(x - x0, y + y0, x + x0, y + y0, color);
			Deccan_Renderer.draw_line2(x - y0, y + x0, x + y0, y + x0, color);
        }
        else {
            Deccan_Renderer.draw_point2(x + x0, y - y0, color);
            Deccan_Renderer.draw_point2(x + y0, y - x0, color);
            Deccan_Renderer.draw_point2(x + y0, y + x0, color);
            Deccan_Renderer.draw_point2(x + x0, y + y0, color);
            Deccan_Renderer.draw_point2(x - x0, y + y0, color);
            Deccan_Renderer.draw_point2(x - y0, y + x0, color);
            Deccan_Renderer.draw_point2(x - y0, y - x0, color);
            Deccan_Renderer.draw_point2(x - x0, y - y0, color);
        }
		if (d < 0) d += 4 * x0++ + 6;
		else d += 4 * (x0++ - y0--) + 10;
	}

	//return true;    
}