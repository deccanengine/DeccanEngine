/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "renderer.h"
#include "draw.h"
#include "texture.h"

#ifdef __STDC__

    typedef struct DE_Renderer {
        void (*clear)(Deccan_Color color);

        void (*set_color)(Deccan_Color color);
        void (*set_pixel_size)(Deccan_Vector2f size);

        Deccan_Color (*get_color)();
        Deccan_Vector2f (*get_pixel_size)();

        void (*draw_point)(Deccan_Vector2i pos, Deccan_Color color);
        void (*draw_line)(Deccan_Vector2i start, Deccan_Vector2i end, Deccan_Color color);
        void (*draw_rect)(Deccan_Rect rect, Deccan_Color color);
        void (*draw_filled_rect)(Deccan_Rect rect, Deccan_Color color);
        void (*draw_circle)(Deccan_Circle circle, Deccan_Color color);
        void (*draw_filled_circle)(Deccan_Circle circle, Deccan_Color color);

        void (*texture_set_color)(Deccan_Texture *texture, Deccan_Color color);
        void (*texture_draw)(Deccan_Vector2i pos, SDL_Texture *texture);
        void (*texture_draw_with_scale)(Deccan_Vector2i pos, Deccan_Vector2f scale, SDL_Texture *texture);
    } DE_Renderer;

    static DE_Renderer Deccan_Renderer = {
        DE_Renderer_clear,

        DE_Renderer_set_color,
        DE_Renderer_set_pixel_size,

        DE_Renderer_get_color,
        DE_Renderer_get_pixel_size,

        DE_Renderer_draw_point,
        DE_Renderer_draw_line,
        DE_Renderer_draw_rect,
        DE_Renderer_draw_filled_rect,
        DE_Renderer_draw_circle,
        DE_Renderer_draw_filled_circle,

        DE_Renderer_texture_set_color,
        DE_Renderer_texture_draw,
        DE_Renderer_texture_draw_with_scale
    };

#elif __cplusplus

#endif