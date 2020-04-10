#pragma once
#include "config.h"
#include "core.h"

typedef struct {
    uint r, g, b, a;
} deccan_Color;

static deccan_Color
    blank  = {  0,   0,   0,   0},
    white  = {255, 255, 255, 255}, black     = {  0,   0,   0, 255},
    grey   = {192, 192, 192, 255}, dark_grey = {128, 128, 128, 255},
	red    = {255,   0,   0, 255}, dark_red  = {128,   0,   0, 255},
    green  = {  0, 255,   0, 255}, dark_green= {  0, 128,   0, 255},
    blue   = {  0,   0, 255, 255}, dark_blue = {  0,   0, 128, 255},
    yellow = {255, 255,   0, 255}, cyan      = {  0, 255, 255, 255}, 
    magenta= {255,   0, 255, 255}, orange    = {255, 165,   0, 255}, 
    violet = {238, 130, 238, 255}, fuchsia   = {255,   0, 255, 255};

void deccan_renderer_clear(deccan_Color color);
void deccan_renderer_set_color(deccan_Color color);