/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Components/DrawableSprite.h"
#include "../Flecs.h"
#include "../../Renderer/RenderTypes.h"
#include "../../Renderer/GenericPipeline.h"
#include "../Components/Transform.h"
#include "../Components/DrawableGeometry.h"
#include "../Components/DrawableSprite.h"

/////////////////////////////////////////////////
// Rendering systems
////////////////////////////////////////////////

DE_PRIV void WorldSpriteRendering(DeccanFlecsIter *it) {
    DeccanCompTransform *transform = DE_FlecsIterColumn(it, "Transform", 1);
    DeccanCompDrawableSprite *sprrender = DE_FlecsIterColumn(it, "DrawableSprite", 2);

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
    DeccanCompDrawableGeometry *arbrender = DE_FlecsIterColumn(it, "DrawableGeometry", 2);

    for (int i = 0; i < it->count; i++) {
        mat4s transmat = glms_mat4_identity();
        glm_translate(transmat.raw, transform->position);
        glm_scale(transmat.raw, transform->scale);

        DeccanDrawAction action;
        action.geometry = &arbrender[i].geometry;
        action.transform = transmat;
        action.material = &arbrender[i].material;
        action.texture = arbrender[i].texture;
        
        DE_GenericPipelineDraw(action);
    }
}

DE_IMPL void DE_SystemInitRendering(void) {
    DE_FlecsSystem(WorldSpriteRendering, "DrawableSpriteRendering", "Transform, DrawableSprite", DECCAN_ECS_TYPE_ON_UPDATE);

    DE_FlecsSystem(WorldArbitaryGeometryRendering, "DrawableGeometryRendering", "Transform, DrawableGeometry", DECCAN_ECS_TYPE_ON_UPDATE);
}
