#pragma once
#include "../../Config.h"
#include "../Color.h"

typedef struct DeccanCompDrawable {
    DeccanColor color;
} DeccanCompDrawable;

void DE_CompDrawableRegister(void);
