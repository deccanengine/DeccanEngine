/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "texture.h"

void DE_Renderer_texture_set_color(Deccan_Texture *texture, Deccan_Color color) {
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

void DE_Renderer_texture_draw(Deccan_Vector2i pos, SDL_Texture *texture) {
    Deccan_Vector2i cam = DE_Core_get_global_engine()->camera;
    
    SDL_Rect rect = {pos.x - cam.x, pos.y - cam.y, 0, 0};
    if(SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) > 0) {
        DE_report("Cannot query texture: %s", SDL_GetError());
    }
    SDL_RenderCopy(DE_Core_get_global_engine()->renderer, texture, NULL, &rect);
}

void DE_Renderer_texture_draw_with_scale(Deccan_Vector2i pos, Deccan_Vector2f scale, SDL_Texture *texture) {
    Deccan_Vector2i cam = DE_Core_get_global_engine()->camera;
    
    SDL_Rect rect = {pos.x - cam.x, pos.y - cam.y, 0, 0};
    if(SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) > 0) {
        DE_report("Cannot query texture: %s", SDL_GetError());
    }
    rect.w *= scale.x; rect.h *= scale.y;
    SDL_RenderCopy(DE_Core_get_global_engine()->renderer, texture, NULL, &rect); 
} 