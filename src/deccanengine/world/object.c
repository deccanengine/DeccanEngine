/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/object.h>
#include <deccanengine/world/scene.h>
#include <deccanengine/world/world.h>
#include <deccanengine/world/flecs.h>

#include "flecs_internal.h"

////////////////////////////////////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////////////////////////////////////

DE_PRIV void object_none_func(deccan_object_t obj) {
    DE_UNUSED(obj);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_object_t deccan_object_new_object(deccan_object_desc_t *desc) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    deccan_object_t obj = {
        .entity = ecs_entity_init(scene->world, &(ecs_entity_desc_t){
            .name = desc->name,
            // TODO: symbol name?
        })
    };

    deccan_object_info_t info = {
        .visible = true,
        .active = true,
        .to_remove = false,
        .is_beginning = true,
    };

    for (int i = 0; i < DE_OBJECT_STAGE_COUNT; i += 1) {
        info.cb[i] = desc->cb[i] != NULL ? desc->cb[i] : object_none_func;
    }

    deccan_object_set_component(obj, "Info", &info);
    deccan_object_make_prefab(obj);

    return obj;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_delete_object(deccan_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_info(obj);
    info->to_remove = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_free_object(deccan_object_t obj) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    deccan_object_info_t *info = deccan_object_get_info(obj);

    if (info->active)
        info->cb[DE_OBJECT_ATEND](obj);

    /* Free */
    ecs_delete(scene->world, obj.entity);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_object_is_valid(deccan_object_t obj) {
    return deccan_object_has_tag(obj, "Info");
}

////////////////////////////////////////////////////////////////////////////////
// Prefab and hierarchy functions
////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_object_t deccan_object_make_copy(deccan_object_t object) {
    deccan_scene_t *scene = deccan_world_get_current_scene();

    deccan_object_t object_inst;
    object_inst.entity = ecs_new_w_entity(scene->world, ECS_INSTANCEOF | object.entity);

    deccan_object_info_t *info = deccan_object_get_info(object_inst);
    info->is_beginning = true;
    info->active = true;

    deccan_object_set_name(object_inst, deccan_object_get_name(object));

    return object_inst;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_make_prefab(deccan_object_t object) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    ecs_add_entity(scene->world, object.entity, EcsPrefab);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_set_parent(deccan_object_t object, deccan_object_t parent) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    ecs_add_entity(scene->world, object.entity, ECS_CHILDOF | parent.entity);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_add_child(deccan_object_t object, deccan_object_t child) {
    deccan_object_set_parent(child, object);
}

////////////////////////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_update(deccan_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_info(obj);

    if (info->to_remove) {
        deccan_object_free_object(obj);
        return;
    }

    if (!info->active)
        return;

    if (info->is_beginning) {
        info->cb[DE_OBJECT_ATBEGINNING](obj);
        info->is_beginning = false;
    }
    else {
        info->cb[DE_OBJECT_ATSTEP](obj);
    }

    // FIXME!: Removing the below line is making the at_beginning callback to
    // be performed twice. This bug used to exist in an ancient version of
    // engine, but this somehow came back once again.
    // A cleaner approach would be to use a custom ECS pipeline which would
    // integrate scene_layer_t and object callbacks. This could fix it.
    deccan_object_set_component(obj, "Info", info);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_render(deccan_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_info(obj);

    if (!info->visible || !info->active)
        return;

    if (!info->is_beginning) {
        info->cb[DE_OBJECT_ATRENDER](obj);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_end(deccan_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_info(obj);

    if (!info->active)
        return;

    info->cb[DE_OBJECT_ATEND](obj);
}

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_set_component(deccan_object_t obj, const char *name, void *component) {
    flecs_set_component(obj.entity, name, component);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *deccan_object_get_component(deccan_object_t obj, const char *name) {
    void *component = flecs_get_component(obj.entity, name);
    if (component == NULL) {
        DE_ERROR("Component %s does not exists on object %s", name, deccan_object_get_name(obj));
        return NULL;
    }
    return component;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_remove_component(deccan_object_t obj, const char *name) {
    flecs_remove_component(obj.entity, name);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_set_name(deccan_object_t obj, const char *name) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    ecs_set_ptr_w_entity(scene->world, obj.entity,
        FLECS__EEcsName,
        sizeof(EcsName),
        &(EcsName){
            .value = deccan_string_new(name)
        }
    );
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL const char *deccan_object_get_name(deccan_object_t obj) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    EcsName *name = ecs_get_mut_w_entity(scene->world, obj.entity, FLECS__EEcsName, NULL);
    return name->value;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_set_tag(deccan_object_t obj, const char *name) {
    flecs_set_tag(obj.entity, name);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_object_has_tag(deccan_object_t obj, const char *name) {
    return flecs_has_tag(obj.entity, name);
}

DE_IMPL deccan_object_info_t *deccan_object_get_info(deccan_object_t obj) {
    return deccan_object_get_component(obj, "Info");
}

////////////////////////////////////////////////////////////////////////////////
// Setters and Getters
////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_object_is_hidden(deccan_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_info(obj);
    return info->visible;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_hide(deccan_object_t obj, bool hide) {
    deccan_object_info_t *info = deccan_object_get_info(obj);
    info->visible = hide;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_object_is_active(deccan_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_info(obj);
    return info->active;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_activate(deccan_object_t obj, bool act) {
    deccan_object_info_t *info = deccan_object_get_info(obj);
    info->active = act;
}
