#include "DrawableGeometry.h"
#include "Drawable.h"
#include "../../Scene/Flecs.h"
#include "../../Scene/Components/Transform.h"
#include "../GenericPipeline.h"
#include "../Texture.h"
#include "../Color.h"

DeccanTexture white_tex;

void Draw(DeccanFlecsIter *it) {
    DeccanCompTransform *transform = DE_FlecsIterColumn(it, "Transform", 1);
    DeccanCompDrawable *drawable = DE_FlecsIterColumn(it, "Drawable", 2);
    DeccanCompDrawableGeometry *drawable_geometry = DE_FlecsIterColumn(it, "DrawableGeometry", 3);

    for (int i = 0; i < it->count; i++) {
        DeccanColor color = drawable[i].color;
        DeccanGeometry geometry = drawable_geometry[i].geometry;

        mat4s transmat = glms_mat4_identity();
        glm_translate(transmat.raw, transform->position);

        geometry.color[0] = color.r; 
        geometry.color[1] = color.g;
        geometry.color[2] = color.b;
        geometry.color[3] = color.a;
        geometry.image = white_tex.image;
        geometry.transform = transmat;

        DE_GenericPipelineDrawGeometry(geometry);        
    }
}

void DE_CompDrawableGeometryRegister(void) {
    DE_TextureCreateBlankRGBA(&white_tex, 1, 1, 0xffffffff);

    DE_FlecsRegisterComponent("DrawableGeometry", sizeof(DeccanCompDrawableGeometry), ECS_ALIGNOF(DeccanCompDrawableGeometry));
    DE_FlecsSystem(Draw, "Draw", "Transform, Drawable, DrawableGeometry", DECCAN_ECS_TYPE_ON_UPDATE);
}
