#pragma once
#include "config.h"
#include "core.h"

typedef struct {
    uint r, g, b, a;
} deccan_Color;

static deccan_Color black = {0, 0, 0, 0};

void deccan_renderer_clear(deccan_Color color);
void deccan_renderer_set_color(deccan_Color color);