/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Components/SpriteRenderer.h"
#include "../Flecs.h"
#include "../../Renderer/RenderTypes.h"
#include "../../Renderer/GenericPipeline.h"
#include "../Components/Transform.h"
#include "../Components/Drawable.h"
#include "../Components/DrawableGeometry.h"
#include "../Components/SpriteRenderer.h"

/////////////////////////////////////////////////
// Rendering systems
////////////////////////////////////////////////

DE_PRIV void WorldSpriteRendering(DeccanFlecsIter *it) {
    DeccanCompTransform *transform = DE_FlecsIterColumn(it, "Transform", 1);
    DeccanCompSpriteRenderer *sprrender = DE_FlecsIterColumn(it, "SpriteRenderer", 2);

    for (int i = 0; i < it->count; i++) {
        mat4s transmat = glms_mat4_identity();
        glm_translate(transmat.raw, transform->position);
        glm_scale(transmat.raw, transform->scale);

        DeccanGeometry quad = DE_PrimitiveCreateQuad();

        DeccanDrawAction action;
        action.geometry = &quad;
        action.transform = transmat;
        action.material = &sprrender[i].material;
        action.texture = sprrender[i].texture;
        
        DE_GenericPipelineDraw(action);
    }
}

DE_PRIV void WorldArbitaryGeometryRendering(DeccanFlecsIter *it) {
    DeccanCompTransform *transform = DE_FlecsIterColumn(it, "Transform", 1);
    DeccanCompDrawable *drawable = DE_FlecsIterColumn(it, "Drawable", 2);
    DeccanCompDrawableGeometry *drawable_geometry = DE_FlecsIterColumn(it, "DrawableGeometry", 3);

    for (int i = 0; i < it->count; i++) {
        mat4s transmat = glms_mat4_identity();
        glm_translate(transmat.raw, transform->position);
        glm_scale(transmat.raw, transform->scale);

        DeccanMaterial material;
        material.color = drawable[i].color;

        DeccanDrawAction action;
        action.geometry = &drawable_geometry[i].geometry;
        action.transform = transmat;
        action.material = &material;
        action.texture = drawable_geometry[i].texture;
        
        DE_GenericPipelineDraw(action);
    }
}

DE_IMPL void DE_SystemInitRendering(void) {
    DE_FlecsSystem(WorldSpriteRendering, "SpriteRendering", "Transform, SpriteRenderer", DECCAN_ECS_TYPE_ON_UPDATE);

    DE_FlecsSystem(WorldArbitaryGeometryRendering, "ArbitaryGeometryRendering", "Transform, Drawable, DrawableGeometry", DECCAN_ECS_TYPE_ON_UPDATE);
}
