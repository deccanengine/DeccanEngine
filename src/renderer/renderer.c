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

void _priv_Renderer_set_pixel_size(Deccan_Vector2f size) {
    SDL_RenderSetScale(Deccan_Core.get_global_engine()->renderer, size.x, size.y);
}

void _priv_Renderer_set_texture_colour(Deccan_Texture *texture, Deccan_Color color) {
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

Deccan_Color _priv_Renderer_get_color() {
    Deccan_Color color;
    SDL_GetRenderDrawColor(Deccan_Core.get_global_engine()->renderer, &color.r, &color.g, &color.b, &color.a);
    return color;
}

Deccan_Vector2f _priv_Renderer_get_pixel_size() {
    Deccan_Vector2f size;
    SDL_RenderGetScale(Deccan_Core.get_global_engine()->renderer, &size.x, &size.y);
    return size;
}

void _priv_Renderer_draw_point(Deccan_Vector2i pos, Deccan_Color color) {
    Deccan_Vector2i cam = Deccan_Core.get_global_engine()->camera;

    Deccan_Renderer.set_color(color);
    SDL_RenderDrawPoint(Deccan_Core.get_global_engine()->renderer, pos.x - cam.x, pos.y - cam.y);
}

void _priv_Renderer_draw_point2(int32_t x, int32_t y, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderDrawPoint(Deccan_Core.get_global_engine()->renderer, x, y);
}

void _priv_Renderer_draw_line(Deccan_Vector2i start, Deccan_Vector2i end, Deccan_Color color) {
    Deccan_Vector2i cam = Deccan_Core.get_global_engine()->camera;

    Deccan_Renderer.set_color(color);
    SDL_RenderDrawLine(Deccan_Core.get_global_engine()->renderer, start.x - cam.x, start.y - cam.y, end.x - cam.x, end.y - cam.y);
}

void _priv_Renderer_draw_line2(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderDrawLine(Deccan_Core.get_global_engine()->renderer, x1, y1, x2, y2);
}

void _priv_Renderer_draw_rect(Deccan_Rect rect, bool fill, Deccan_Color color) {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    SDL_Rect sr = {rect.x - engine->camera.x, rect.y - engine->camera.y, rect.w, rect.h};

    Deccan_Renderer.set_color(color);
    if(fill) { SDL_RenderFillRect(engine->renderer, &sr); }
    else { SDL_RenderDrawRect(engine->renderer, &sr); }
}

void _priv_Renderer_draw_circle(Deccan_Circle circle, bool fill, Deccan_Color color) {
    Deccan_Info *engine = Deccan_Core.get_global_engine();

    int x = circle.x - engine->camera.x;
    int y = circle.y - engine->camera.y;
    int radius = circle.radius;
    
    int x0 = 0;
	int y0 = circle.radius;
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

void _priv_Renderer_draw_texture(Deccan_Vector2i pos, SDL_Texture *texture) {
    Deccan_Vector2i cam = Deccan_Core.get_global_engine()->camera;
    
    SDL_Rect rect = { pos.x - cam.x, pos.y - cam.y, 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(Deccan_Core.get_global_engine()->renderer, texture, NULL, &rect);
}

void _priv_Renderer_draw_scaled_texture(Deccan_Vector2i pos, Deccan_Vector2f scale, SDL_Texture *texture) {
    int32_t width, height;
    Deccan_Vector2i cam = Deccan_Core.get_global_engine()->camera;
    
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    
    SDL_Rect rect = {pos.x - cam.x, pos.y - cam.y, width*scale.x, height*scale.y};
    SDL_RenderCopy(Deccan_Core.get_global_engine()->renderer, texture, NULL, &rect); 
} 