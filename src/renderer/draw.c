/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "draw.h"

#define DWC_FUNC void f(SDL_Renderer *renderer, DE_Vector2i camera)
#define DWC_FUNCREF f

#define DWT_FUNC void f(SDL_Renderer *renderer, DE_Vector2i camera)
#define DWT_FUNCREF f

void DE_draw_with_color(void (*DE_dwc_drawcall)(SDL_Renderer *renderer, DE_Vector2i camera), DE_Color color) {
    DE_Info *engine = DE_Core_get_global_engine(); 
    
    DE_Color def = DE_Renderer_get_color();
    DE_Renderer_set_color(color);

    DE_dwc_drawcall(engine->renderer, engine->camera);

    DE_Renderer_set_color(def);
}

void DE_draw_with_target(void (*DE_dwt_drawcall)(SDL_Renderer *renderer, DE_Vector2i camera), float angle, SDL_Point *center, SDL_RendererFlip flip) {
    // WIP. Do not use
    DE_Info *engine = DE_Core_get_global_engine();

    int width, height;
    int access = SDL_TEXTUREACCESS_TARGET;
    uint32_t format = SDL_PIXELFORMAT_RGBA8888; 

    SDL_Texture *buffer = SDL_GetRenderTarget(engine->renderer);
    if (buffer == NULL) {
        SDL_RenderGetLogicalSize(engine->renderer, &width, &height);
        if (width == 0 || height == 0) {
            if (SDL_GetRendererOutputSize(engine->renderer, &width, &height) < 0) {
                DE_error("Failed to retrive renderer output size: %s", SDL_GetError());
            }
        }
    }
    else {
        if (SDL_QueryTexture(buffer, &format, &access, &width, &height) < 0) {
            DE_error("Failed to retrive render target info: %s", SDL_GetError());
        }
    }

    SDL_Texture *target = SDL_CreateTexture(engine->renderer, format, access, width, height);
    if(target == NULL || SDL_SetRenderTarget(engine->renderer, target) < 0) { DE_error("Cannot draw with target: %s", SDL_GetError()); } 

    SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_BLEND); 

    DE_dwt_drawcall(engine->renderer, engine->camera);

    if(SDL_SetRenderTarget(engine->renderer, buffer) < 0) {
        DE_error("Default render buffer cannot be set: %s", SDL_GetError());
    }

    if(SDL_RenderCopyEx(engine->renderer, target, NULL, NULL, angle, center, flip) < 0) {
        DE_error("Cannot draw with target2: %s", SDL_GetError());
    }

    SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_NONE); 
}

void DE_Renderer_draw_point(DE_Vector2i pos, DE_Color color) {
    DE_draw_with_color(({
        DWC_FUNC {
            SDL_RenderDrawPoint(renderer, pos.x - camera.x, pos.y - camera.y);
        } DWC_FUNCREF;
    }), color);
}

void DE_Renderer_draw_line(DE_Vector2i start, DE_Vector2i end, DE_Color color) {
    DE_draw_with_color(({
        DWC_FUNC { 
            SDL_RenderDrawLine(renderer, start.x - camera.x, start.y - camera.y, end.x - camera.x, end.y - camera.y);
        } DWC_FUNCREF;
    }), color);
}

void DE_Renderer_draw_rect(DE_Rect rect, DE_Color color) {
    DE_draw_with_color(({
        DWC_FUNC { 
            SDL_Rect sr = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
            SDL_RenderDrawRect(renderer, &sr);
        } DWC_FUNCREF;
    }), color);
}

void DE_Renderer_draw_rect_ext(DE_Rect rect, DE_Color color, float angle) {
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
}

void DE_Renderer_draw_filled_rect(DE_Rect rect, DE_Color color) {
    DE_draw_with_color(({
        DWC_FUNC { 
            SDL_Rect sr = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
            SDL_RenderFillRect(renderer, &sr);
        } DWC_FUNCREF;
    }), color); 
}

void DE_Renderer_draw_circle(DE_Circle circle, DE_Color color) {
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

void DE_Renderer_draw_filled_circle(DE_Circle circle, DE_Color color) {
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