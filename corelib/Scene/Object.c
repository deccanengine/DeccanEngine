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

    obj->entity = ecs_new_w_entity(scene->world, 0);

	DeccanObjectInfo info;
	info.visible  = true;
    info.active   = true;
    info.to_remove = false;
    info.is_beginning = true;
    info.AtFirstFrame = NULL_OBJFUNC;
    info.AtBeginning = NULL_OBJFUNC;
    info.AtStep = NULL_OBJFUNC;
    info.AtRender = NULL_OBJFUNC;
    info.AtEnd = NULL_OBJFUNC;

	DE_ObjectSetName(obj, name);
	DE_ObjectSetInfo(obj, &info);

	obj->info = DE_ObjectGetInfo(obj);

    return obj;
}

void DE_ObjectDeleteObject(DeccanGameObject *obj) {
    PTR_NULLCHECK(obj);

    //obj->toRemove = true;
}

void DE_ObjectFreeObject(DeccanGameObject *obj) {
    PTR_NULLCHECK(obj);

    DeccanGameScene *scene = DE_SceneCurrentScene();
	DeccanObjectInfo *info = DE_ObjectGetInfo(obj);

	info->AtEnd(obj);

    /* Free the messaging system */
    //DE_VarQuit(&obj->vars);

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
// Prefab and hierarchy functions
////////////////////////////////////////////////

DeccanGameObject *DE_ObjectMakeCopy(DeccanGameObject *object) {
    DeccanGameScene *scene = DE_SceneCurrentScene();

	DeccanGameObject *object_inst = DE_Mem_New(sizeof(DeccanGameObject), 1);
	object_inst->entity = ecs_new_w_entity(scene->world, ECS_INSTANCEOF | object->entity);
	object_inst->info = DE_ObjectGetInfo(object_inst);
	object_inst->info->is_beginning = true;
	object_inst->info->active = true;

    return object_inst;
}

void DE_ObjectMakePrefab(DeccanGameObject *object) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_add_entity(scene->world, object->entity, EcsPrefab);
}

void DE_ObjectSetParent(DeccanGameObject *object, DeccanGameObject *parent) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_add_entity(scene->world, object->entity, ECS_CHILDOF | parent->entity);
}

void DE_ObjectAddChild(DeccanGameObject *object, DeccanGameObject *child) {
    DE_ObjectSetParent(child, object);
}

/////////////////////////////////////////////////
// Update
////////////////////////////////////////////////

void DE_ObjectUpdate(DeccanGameObject *obj) {
    DeccanObjectInfo *info = DE_ObjectGetInfo(obj);

	if(info->to_remove) {
        DE_ObjectFreeObject(obj);
        return;
    }

    if(!info->active) {
        return;
    }

    if(info->is_beginning == true) {
        /* Initialize messaging system */
        //DE_VarInit(&obj->vars);

        info->AtBeginning(obj);
        info->is_beginning = false;
    }
    else {
		info->AtStep(obj);
    }
}

void DE_ObjectRender(DeccanGameObject *obj) {
    DeccanObjectInfo *info = DE_ObjectGetInfo(obj);

	if(!info->visible) {
        return;
    }

    if(!info->is_beginning) {
        info->AtRender(obj);
    }
}

void DE_ObjectEnd(DeccanGameObject *obj) {
    PTR_NULLCHECK(obj);

	DeccanObjectInfo *info = DE_ObjectGetInfo(obj);
    info->AtEnd(obj);
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

DeccanObjectInfo *DE_ObjectGetInfo(DeccanGameObject *object) {
	DeccanGameScene *scene = DE_SceneCurrentScene();
	DeccanObjectInfo *info = ecs_get_mut_w_entity(scene->world, object->entity, ecs_lookup(scene->world, "Info"), NULL);
	return info;
}

void DE_ObjectSetInfo(DeccanGameObject *object, DeccanObjectInfo *info) {
	DeccanGameScene *scene = DE_SceneCurrentScene();
	ecs_set_ptr_w_entity(scene->world, object->entity, ecs_lookup(scene->world, "Info"), sizeof(DeccanObjectInfo), info);
}

bool DE_ObjectIsHidden(DeccanGameObject *obj) {
//    return obj->visible;
}

void DE_ObjectHide(DeccanGameObject *obj, bool hide) {
//    obj->visible = hide;
}

bool DE_ObjectIsActive(DeccanGameObject *obj) {
//    return obj->active;
}

void DE_ObjectActivate(DeccanGameObject *obj, bool act) {
//    obj->active = act;
}

#undef PTR_NULLCHECK
