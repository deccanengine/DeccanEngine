#pragma once
#include "../../Config.h"
#include "../RenderTypes.h"

typedef struct DeccanCompDrawableGeometry {
    DeccanGeometry geometry;
} DeccanCompDrawableGeometry;

void DE_CompDrawableGeometryRegister(void);
