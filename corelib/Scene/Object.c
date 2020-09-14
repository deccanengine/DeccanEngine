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

static struct {
    int32_t zAccum;
    GameObject defaultObj;
} Object_Info = {
    .zAccum = 0,
    .defaultObj = {0}
};

#define PTR_NULLCHECK(x) if(x == NULL) { return; }

/////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////

GameObject *Object_NewObject(const char *name) {
    GameScene *scene = Scene_CurrentScene();
    GameObject *obj = DE_Mem_New(sizeof(GameObject), 1);

    obj->entity = ecs_new_w_type(scene->world, 0);

    ecs_set_ptr_w_entity(scene->world, obj->entity,
        ecs_lookup(scene->world, "GameObject"), sizeof(GameObject), obj);
    ecs_set_ptr_w_entity(scene->world, obj->entity, FLECS__EEcsName,
        sizeof(EcsName), &(EcsName){DE_String_New(name)});

    obj->order.z = (float)Object_Info.zAccum++;

    obj->visible    = true;
    obj->active     = true;
    obj->toRemove   = false;

    /* Initialize messaging system */
    DE_Var_Init(&obj->vars);

    obj->is_beginning = true;
    obj->AtFirstFrame = NULL_OBJFUNC;
    obj->AtBeginning = NULL_OBJFUNC;
    obj->AtStep = NULL_OBJFUNC;
    obj->AtRender = NULL_OBJFUNC;
    obj->AtEnd = NULL_OBJFUNC;

    return obj;
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
    DE_Var_Quit(&obj->vars);

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

void AddObjectToArray(GameObject *object) {
    GameScene *scene = Scene_CurrentScene();
    int length = stbds_arrlen(scene->objects);

    if(length > 0 && object->order.z != -1) {
        for(int i=0; i<length; i++) {
            if(object->order.z >= scene->objects[i]->order.z) {
                if(i+1 >= length) {
                    goto _push;
                }

                if(object->order.z < scene->objects[i+1]->order.z) {
                    stbds_arrins(scene->objects, i+1, object);
                    break;
                }
            }
            else {
                stbds_arrins(scene->objects, i, object);
                break;
            }
        }
    }
    else {
_push:
        if(stbds_arrput(scene->objects, object) != object) {
            DE_REPORT("Cannot instantiate object: %s", ecs_get_name(scene->world, object->entity));
            return;
        }
    }
}

void Object_InstantiateObject(GameObject *object) {
    PTR_NULLCHECK(object);
    AddObjectToArray(object);
}

GameObject *Object_GetObject(const char *name) {
    GameScene *scene = Scene_CurrentScene();
    ecs_entity_t obj = ecs_lookup(scene->world, name);
    return ecs_get_mut_w_entity(scene->world, obj, ecs_lookup(scene->world, "GameObject"), NULL);
}

void Object_GetObjectOfType(const char *name, void(*func)(GameObject *obj)) {

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
    GameScene *scene = Scene_CurrentScene();
    DeccanComponent comp = DE_Flecs_LookupComponent(name);
    if(comp.key == NULL) {
        DE_WARN("Component %s is not a valid registered component in the scene", name);
        return;
    }

    ecs_set_ptr_w_entity(scene->world, obj->entity, comp.id, comp.size, component);
}

void *Object_GetComponent(GameObject *obj, const char *name) {
    GameScene *scene = Scene_CurrentScene();
    return ecs_get_mut_w_entity(scene->world, obj->entity, ecs_lookup(scene->world, name), NULL);
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
