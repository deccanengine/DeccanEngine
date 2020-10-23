/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Object.h"
#include "Scene.h"
#include "../Core/Core.h"
#include "Flecs.h"

#define PTR_NULLCHECK(x) if(x == NULL) { return; }

/////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////

GameObject *Object_NewObject(const char *name) {
    GameScene *scene = Scene_CurrentScene();
    GameObject *obj = DE_Mem_New(sizeof(GameObject), 1);

    obj->entity = ecs_new_w_entity(scene->world, ECS_CHILDOF | 0);

    ecs_set_ptr_w_entity(scene->world, obj->entity,
        ecs_lookup(scene->world, "GameObject"), sizeof(GameObject), obj);

    Object_SetName(obj, name);

    obj->visible  = true;
    obj->active   = true;
    obj->toRemove = false;

    obj->is_beginning = true;
    obj->AtFirstFrame = NULL_OBJFUNC;
    obj->AtBeginning = NULL_OBJFUNC;
    obj->AtStep = NULL_OBJFUNC;
    obj->AtRender = NULL_OBJFUNC;
    obj->AtEnd = NULL_OBJFUNC;

    return obj;
}

GameObject *Object_MakeCopy(GameObject *object) {
    GameScene *scene = Scene_CurrentScene();
    GameObject *object_inst = Object_NewObject(Object_GetName(object));

    object_inst->entity = ecs_new_w_entity(scene->world, ECS_INSTANCEOF | object->entity);

    object_inst->visible = object->visible;
    object_inst->active = object->active;

    object_inst->AtFirstFrame = object->AtFirstFrame;
    object_inst->AtBeginning = object->AtBeginning;
    object_inst->AtStep = object->AtStep;
    object_inst->AtRender = object->AtRender;
    object_inst->AtEnd = object->AtEnd;

    ecs_set_ptr_w_entity(scene->world, object_inst->entity,
        ecs_lookup(scene->world, "GameObject"), sizeof(GameObject), object_inst);

    return object_inst;
}

void Object_DeleteObject(GameObject *obj) {
    PTR_NULLCHECK(obj);

    obj->toRemove = true;
}

void Object_FreeObject(GameObject *obj) {
    PTR_NULLCHECK(obj);

    GameScene *scene = Scene_CurrentScene();

    obj->AtEnd(obj);

    /* Free the messaging system */
    DE_VarQuit(&obj->vars);

    /* Index of the object in the array */
    for(int i = 0; i < stbds_arrlen(scene->objects); i++) {
        if(scene->objects[i] == obj) {
            /* Remove from the array */
            stbds_arrdel(scene->objects, i);
        }
    }

    /* Free */
    ecs_delete(scene->world, obj->entity);
    DE_Mem_Delete(obj);
}

/////////////////////////////////////////////////
// Update
////////////////////////////////////////////////

void Object_Update(GameObject *obj) {
    if(obj->toRemove) {
        Object_FreeObject(obj);
        return;
    }

    if(!obj->active) {
        return;
    }

    if(obj->is_beginning == true) {
        /* Initialize messaging system */
        DE_VarInit(&obj->vars);

        obj->AtBeginning(obj);
        obj->is_beginning = false;
    }
    else {
        obj->AtStep(obj);
    }
}

void Object_Render(GameObject *obj) {
    if(!obj->visible) {
        return;
    }

    if(!obj->is_beginning) {
        obj->AtRender(obj);
    }
}

void Object_End(GameObject *obj) {
    PTR_NULLCHECK(obj);

    obj->AtEnd(obj);
}

/////////////////////////////////////////////////
// Component
////////////////////////////////////////////////

void Object_SetComponent(GameObject *obj, const char *name, void *component) {
    DE_Flecs_SetComponent(obj->entity, name, component);
}

void *Object_GetComponent(GameObject *obj, const char *name) {
    return DE_Flecs_GetComponent(obj->entity, name);
}

void Object_SetName(GameObject *obj, const char *name) {
    GameScene *scene = Scene_CurrentScene();
    ecs_set_ptr_w_entity(scene->world, obj->entity, FLECS__EEcsName,
        sizeof(EcsName), &(EcsName){DE_String_New(name)});
}

const char *Object_GetName(GameObject *obj) {
    GameScene *scene = Scene_CurrentScene();
    EcsName *name = ecs_get_mut_w_entity(scene->world, obj->entity, FLECS__EEcsName, NULL);
    return name->value;
}

void Object_SetTag(GameObject *obj, const char *name) {
    DE_Flecs_SetTag(obj->entity, name);
}

bool Object_HasTag(GameObject *obj, const char *name) {
    return DE_Flecs_HasTag(obj->entity, name);
}

/////////////////////////////////////////////////
// Setters and Getters
////////////////////////////////////////////////

bool Object_IsHidden(GameObject *obj) {
    return obj->visible;
}

void Object_Hide(GameObject *obj, bool hide) {
    obj->visible = hide;
}

bool Object_IsActive(GameObject *obj) {
    return obj->active;
}

void Object_Activate(GameObject *obj, bool act) {
    obj->active = act;
}

#undef PTR_NULLCHECK
