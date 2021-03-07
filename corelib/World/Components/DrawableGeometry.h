#pragma once
#include "../../Config.h"
#include "../../Renderer/RenderTypes.h"

typedef struct DeccanCompDrawableGeometry {
    DeccanGeometry geometry;
} DeccanCompDrawableGeometry;

void DE_CompDrawableGeometryRegister(void);
