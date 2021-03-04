#include "DrawableGeometry.h"
#include "../../Scene/Flecs.h"

void Draw(DeccanFlecsIter *it) {
    DeccanCompDrawable *drawable = DE_FlecsIterColumn(it, "DeccanCompDrawable", 1);
    DeccanCompDrawableGeometry *drawable_geometry = DE_FlecsIterColumn(it, "DeccanCompDrawableGeometry", 2);

    for (int i = 0; i < it->count; i++) {
        
    }
}

void DE_CompDrawableGeometryRegister(void) {
    DE_FlecsRegisterComponent("DrawableGeometry", sizeof(DeccanCompDrawableGeometry), ECS_ALIGNOF(DeccanCompDrawableGeometry));
}
