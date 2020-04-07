#pragma once
#include "core.h"

typedef struct {
    uint r, g, b, a;
} deccan_color;

static deccan_color black = {0, 0, 0, 0};

void deccan_clear_screen(deccan_info *engine, deccan_color color);
void deccan_set_render_color(deccan_info *engine, deccan_color color);