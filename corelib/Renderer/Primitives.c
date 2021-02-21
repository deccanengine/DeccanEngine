/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Primitives.h"
#include "Renderer.h"
#include "Camera.h"

#define DE_DRAW_BEGIN()                            \
vec2 camera; DE_CameraGetPosition(camera);         \
SDL_Renderer *renderer = DE_RendererGetRenderer(); \
DeccanColor def = DE_RendererGetColor();           \
SDL_BlendMode blend;                               \
DE_RendererSetColor(color);                        \
SDL_GetRenderDrawBlendMode(renderer, &blend);

#define DE_DRAW_END()                              \
DE_RendererSetColor(def);                          \
SDL_SetRenderDrawBlendMode(renderer,  blend);

void DE_DrawPoint(vec2 pos, DeccanColor color) {
#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    SDL_RenderDrawPoint(renderer, pos[0] - camera[0], pos[1] - camera[1]);
    DE_DRAW_END();
#else

#endif
}

void DE_DrawLine(vec2 start, vec2 end, DeccanColor color) {
#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    SDL_RenderDrawLine(renderer, start[0] - camera[0], start[1] - camera[1], end[0] - camera[0], end[1] - camera[1]);
    DE_DRAW_END();
#else

#endif
}

void DE_DrawRect(vec4 rect, DeccanColor color) {
#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    SDL_Rect sr = {rect[0] - camera[0], rect[1] - camera[1], rect[2], rect[3]};
    SDL_RenderDrawRect(renderer, &sr);
    DE_DRAW_END();
#else

#endif
}

void DE_DrawFilledRect(vec4 rect, DeccanColor color) {
#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    SDL_Rect sr = {rect[0] - camera[0], rect[1] - camera[1], rect[2], rect[3]};
    SDL_RenderFillRect(renderer, &sr);
    DE_DRAW_END();
#else

#endif
}

void DE_DrawCircle(vec3 circle, DeccanColor color) {
    if(!circle[2]) { return; }

#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    int x = circle[0] - camera[0];
    int y = circle[1] - camera[1];

    int x0 = 0;
    int y0 = circle[2];
    int d = 3 - 2 * circle[2];

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
    DE_DRAW_END();
#else

#endif
}

void DE_DrawFilledCircle(vec3 circle, DeccanColor color) {
    if(!circle[2]) { return; }

#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    int x = circle[0] - camera[0];
    int y = circle[1] - camera[1];

    int x0 = 0;
    int y0 = circle[2];
    int d = 3 - 2 * circle[2];

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
    DE_DRAW_END();
#else

#endif
}
