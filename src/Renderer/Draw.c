/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

#define DE_DRAW_BEGIN()                          \
Vector2f camera = Camera_GetPosition();          \
SDL_Renderer *renderer = Renderer_GetRenderer(); \
Color def = Renderer_GetColor();                 \
SDL_BlendMode blend;                             \
Renderer_SetColor(color);                        \
SDL_GetRenderDrawBlendMode(renderer, &blend);

#define DE_DRAW_END()                            \
Renderer_SetColor(def);                          \
SDL_SetRenderDrawBlendMode(renderer,  blend);

void Draw_Point(Vector2f pos, Color color) {
#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    SDL_RenderDrawPoint(renderer, pos.x - camera.x, pos.y - camera.y);
    DE_DRAW_END();
#else

#endif
}

void Draw_Line(Vector2f start, Vector2f end, Color color) {
#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    SDL_RenderDrawLine(renderer, start.x - camera.x, start.y - camera.y, end.x - camera.x, end.y - camera.y);
    DE_DRAW_END();
#else

#endif
}

void Draw_Rect(Rect rect, Color color) {
#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    SDL_Rect sr = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
    SDL_RenderDrawRect(renderer, &sr);
    DE_DRAW_END();
#else

#endif
}

void Draw_FilledRect(Rect rect, Color color) {
#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
    SDL_Rect sr = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
    SDL_RenderFillRect(renderer, &sr);
    DE_DRAW_END();
#else

#endif
}

void Draw_Circle(Circle circle, Color color) {
    if(!circle.radius) { return; }

#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
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
    DE_DRAW_END();   
#else

#endif
}

void Draw_FilledCircle(Circle circle, Color color) {
    if(!circle.radius) { return; }

#ifdef DECCAN_RENDERER_SDL
    DE_DRAW_BEGIN();
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
    DE_DRAW_END();    
#else

#endif
}