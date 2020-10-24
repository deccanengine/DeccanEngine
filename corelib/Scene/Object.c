/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Object.h"
#include "Scene.h"
#include "Flecs.h"

#define PTR_NULLCHECK(x) if(x == NULL) { return; }

/////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////

DeccanGameObject *DE_ObjectNewObject(const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    DeccanGameObject *obj = DE_Mem_New(sizeof(DeccanGameObject), 1);

    obj->entity = ecs_new_w_entity(scene->world, ECS_CHILDOF | 0);

    ecs_set_ptr_w_entity(scene->world, obj->entity,
        ecs_lookup(scene->world, "DeccanGameObject"), sizeof(DeccanGameObject), obj);

    DE_ObjectSetName(obj, name);

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

DeccanGameObject *DE_ObjectMakeCopy(DeccanGameObject *object) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    DeccanGameObject *object_inst = DE_ObjectNewObject(DE_ObjectGetName(object));

    object_inst->entity = ecs_new_w_entity(scene->world, ECS_INSTANCEOF | object->entity);

    object_inst->visible = object->visible;
    object_inst->active = object->active;

    object_inst->AtFirstFrame = object->AtFirstFrame;
    object_inst->AtBeginning = object->AtBeginning;
    object_inst->AtStep = object->AtStep;
    object_inst->AtRender = object->AtRender;
    object_inst->AtEnd = object->AtEnd;

    ecs_set_ptr_w_entity(scene->world, object_inst->entity,
        ecs_lookup(scene->world, "DeccanGameObject"), sizeof(DeccanGameObject), object_inst);

    return object_inst;
}

void DE_ObjectDeleteObject(DeccanGameObject *obj) {
    PTR_NULLCHECK(obj);

    obj->toRemove = true;
}

void DE_ObjectFreeObject(DeccanGameObject *obj) {
    PTR_NULLCHECK(obj);

    DeccanGameScene *scene = DE_SceneCurrentScene();

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

void DE_ObjectUpdate(DeccanGameObject *obj) {
    if(obj->toRemove) {
        DE_ObjectFreeObject(obj);
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

void DE_ObjectRender(DeccanGameObject *obj) {
    if(!obj->visible) {
        return;
    }

    if(!obj->is_beginning) {
        obj->AtRender(obj);
    }
}

void DE_ObjectEnd(DeccanGameObject *obj) {
    PTR_NULLCHECK(obj);

    obj->AtEnd(obj);
}

/////////////////////////////////////////////////
// Component
////////////////////////////////////////////////

void DE_ObjectSetComponent(DeccanGameObject *obj, const char *name, void *component) {
    DE_FlecsSetComponent(obj->entity, name, component);
}

void *DE_ObjectGetComponent(DeccanGameObject *obj, const char *name) {
    return DE_FlecsGetComponent(obj->entity, name);
}

void DE_ObjectSetName(DeccanGameObject *obj, const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_set_ptr_w_entity(scene->world, obj->entity, FLECS__EEcsName,
        sizeof(EcsName), &(EcsName){DE_String_New(name)});
}

const char *DE_ObjectGetName(DeccanGameObject *obj) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    EcsName *name = ecs_get_mut_w_entity(scene->world, obj->entity, FLECS__EEcsName, NULL);
    return name->value;
}

void DE_ObjectSetTag(DeccanGameObject *obj, const char *name) {
    DE_FlecsSetTag(obj->entity, name);
}

bool DE_ObjectHasTag(DeccanGameObject *obj, const char *name) {
    return DE_FlecsHasTag(obj->entity, name);
}

/////////////////////////////////////////////////
// Setters and Getters
////////////////////////////////////////////////

bool DE_ObjectIsHidden(DeccanGameObject *obj) {
    return obj->visible;
}

void DE_ObjectHide(DeccanGameObject *obj, bool hide) {
    obj->visible = hide;
}

bool DE_ObjectIsActive(DeccanGameObject *obj) {
    return obj->active;
}

void DE_ObjectActivate(DeccanGameObject *obj, bool act) {
    obj->active = act;
}

#undef PTR_NULLCHECK
