#pragma once

typedef struct {
    uint r, g, b, a;
} Deccan_Color;

typedef struct _priv_ColorList {
    Deccan_Color blank, 
    white, black, grey, dark_grey,
    red, dark_red, green, dark_green,
    blue, dark_blue, yellow, cyan,
    magenta, orange, violet, fuchsia;
} _priv_ColorList;

static _priv_ColorList Deccan_ColorList = {
    {  0,   0,   0,   0},
    {255, 255, 255, 255}, {  0,   0,   0, 255},
    {192, 192, 192, 255}, {128, 128, 128, 255},
	{255,   0,   0, 255}, {128,   0,   0, 255},
    {  0, 255,   0, 255}, {  0, 128,   0, 255},
    {  0,   0, 255, 255}, {  0,   0, 128, 255},
    {255, 255,   0, 255}, {  0, 255, 255, 255}, 
    {255,   0, 255, 255}, {255, 165,   0, 255}, 
    {238, 130, 238, 255}, {255,   0, 255, 255}
};