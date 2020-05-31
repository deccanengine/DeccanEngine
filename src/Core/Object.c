/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Object.h>
#include <Deccan/Scene.h>
#include <Deccan/Core.h>

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

void _msg_send(GameObject *obj, const char *msg) {
    Msg_Send(&obj->msg, msg);
}

bool _msg_receive(GameObject *obj, const char *msg) {
    return Msg_Receive(&obj->msg, msg);
}

GameObject *Object_NewObject(const char *name, const char *type) {
    
    GameObject *obj = DE_NEW(GameObject, 1);
    
    obj->name = DE_NEWSTRING(name);
    obj->type = DE_NEWSTRING(type);
    
    obj->order.z = Object_Info.zAccum++;
    //obj->angle   = 0.0f;

    obj->visible = true;
    
    Msg_Init(&obj->msg, DECCAN_OBJ_MSG_COUNT, DECCAN_OBJ_MSG_LENGTH);
    obj->SendMessage = _msg_send;
    obj->ReceiveMessage = _msg_receive;
    
    obj->is_beginning = true;
    obj->AtFirstFrame = NULL_OBJFUNC;
    obj->AtBeginning = NULL_OBJFUNC;
    obj->AtStep = NULL_OBJFUNC;
    obj->AtRender = NULL_OBJFUNC;
    obj->AtEnd = NULL_OBJFUNC;

    obj->components = NULL;
    obj->component_length = 0;

    return obj;
}

void Object_DeleteObject(GameObject *obj) {
    PTR_NULLCHECK(obj);

    int32_t index = 0;
    GameScene *scene = Scene_CurrentScene();

    /* Index of the object in the array */
    while(obj != scene->objects[index] && index < stbds_arrlen(scene->objects)) {
        index++;
    }

    obj->AtEnd(obj);

    /* Free the name */
    if(obj->name != NULL) {
        free(obj->name);
        obj->name = NULL;
    }

    /* Free the type */
    if(obj->type != NULL) {
        free(obj->type);
        obj->type = NULL;
    }

    /* Remove from the array */
    stbds_arrdel(scene->objects, index);
    scene->object_count--;

    /* Free */
    free(obj);
    obj = NULL;
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
            DE_REPORT("Cannot instantiate object: %s", object->name); return;
        }
    }
    scene->object_count++;
}

void Object_InstantiateObject(GameObject *object) {
    PTR_NULLCHECK(object);
    AddObjectToArray(object);
}

GameObject *Object_GetObject(const char *name) {
    GameScene *scene = Scene_CurrentScene();
    for(int i=0; i<scene->object_count; i++) {
        if(!strcmp(scene->objects[i]->name, name)) {
            return scene->objects[i];
        }
    }
    
    DE_REPORT("GameObject not found: %s", name);
    return &Object_Info.defaultObj;
}

void Object_GetObjectOfType(const char *name, void(*func)(GameObject *obj)) {
    GameScene *scene = Scene_CurrentScene();
    for(int i=0; i<scene->object_count; i++) {
        if(!strcmp(scene->objects[i]->type, name)) {
            func(scene->objects[i]);
        }
    }
}

/////////////////////////////////////////////////
// Component
////////////////////////////////////////////////

void Object_SetComponent(GameObject *obj, int32_t id, void *component) {
    /* Find the component */
    for(int i=0; i<obj->component_length; i++) {
        if(obj->components[i]->id == id) {
            obj->components[i]->address = component;
            return;
        }
    }

    /* Create a new one if not found */
    Component *comp = DE_NEW(Component, 1);
    comp->id = id;
    comp->address = component;

    stbds_arrput(obj->components, comp);
    obj->component_length++;
}

void *Object_GetComponent(GameObject *obj, int32_t id) {
    for(int i=0; i<obj->component_length; i++) {
        if(obj->components[i]->id == id) {
            return (void*)obj->components[i]->address;
        }
    }

    /* Component not found! Quite impossible due to ID system */
    //DE_ERROR("Component not found: ID: %d for GameObject: %s", id, obj->info.name);
    return NULL;
}

/////////////////////////////////////////////////
// Setters and Getters
////////////////////////////////////////////////

/***********
 * Position
 ***********/

/*
void Object_SetPosition(GameObject *obj, Vector2f pos) {
    Position *p = OBJECT_GetComponent(obj, Position);
    p->x = pos.x;
    p->y = pos.y;
    p->z = pos.z;
    //obj->position = pos;
}

Vector2f Object_GetPosition(GameObject *obj) {
    return obj->position;
}
*/
/***********
 * Angle
 ***********/
/*
void _clamp_angle(double *angle) {
    while(*angle > 360) { *angle -= 360; }
    while(*angle <   0) { *angle += 360; }
}

void Object_SetAngle(GameObject *obj, double angle) {
    PTR_NULLCHECK(obj);
    
    _clamp_angle(&angle);
    obj->angle = angle;
}

double Object_GetAngle(GameObject *obj) {
    PTR_NULLCHECK(obj);
    
    _clamp_angle(&obj->angle);
    return obj->angle;
}
*/
/***********
 * Z-Order
 ***********/
/*
void Object_SetZOrder(GameObject *obj, int32_t z) {
    PTR_NULLCHECK(obj);

    if(obj->order.z == z) {
        return;
    }

    GameScene *scene = Scene_CurrentScene();

    for(int i=0; i<stbds_arrlen(scene->objects); i++) {
        /* Finding itself */
        //if(scene->objects[i] == obj) {
            /* Remove the old object */
            /*stbds_arrdel(scene->objects, i);
            scene->object_count--;

            /* Add the same object with different Z-order */
            /*obj->order.z = z;
            AddObjectToArray(obj);
            return;
        }
    }
}

int32_t Object_GetZOrder(GameObject *obj) {
    return obj->order.z;
}
*/
/***********
 * Status
 ***********/

bool Object_IsHidden(GameObject *obj) {
    return obj->visible;
}

void Object_Hide(GameObject *obj, bool hide) {
    obj->visible = hide;
}

/***********
 * Collider
 ***********/
/*
Collider Object_GetCollider(GameObject *obj) {
    return obj->collider;
}

void Object_SetCollider(GameObject *obj, Collider collider) {
    obj->collider = collider;
}
*/
/////////////////////////////////////////////////
// Rotation functions
////////////////////////////////////////////////

/*
int _angle_diff(double a1, double a2) {
    return ((((int)(a1 - a2) % 360) + 180) % 360) - 180;
}

/* WIP */
/*void Object_Rotate(GameObject *obj, double angle, int speed) {
    PTR_NULLCHECK(obj);

    if(speed <= 0) { 
        obj->angle = angle; 
        return;
    }

    _clamp_angle(&obj->angle);
    _clamp_angle(&angle);

    //double doaa = 180.0f - abs(abs(obj->angle - angle) - 180.0f);
    int doaa = _angle_diff(obj->angle, angle);
    
    if(doaa == 0 || doaa == (speed * -1)) { return; }
    else {
        bool is_positive = (doaa >= 0);
        double new_angle = obj->angle + ((is_positive ? -1.0f : 1.0f) * (speed)); //* (Core_GetDeltaTime()));
    
        //double dnaa = 180.0f - abs(abs(new_angle - angle) - 180.0f);
        int dnaa = _angle_diff(new_angle, angle);
        //printf("angle_diff = %d is_positive = %d\n", dnaa, is_positive);

        if((dnaa >= 0) ^ is_positive) {
            new_angle = angle;
        }
        
        obj->angle = new_angle;
    }
}

void Object_RotateTowardsObject(GameObject *obj, GameObject *target, int speed) {
    PTR_NULLCHECK(target);
    Object_RotateTowardsPosition(obj, target->position, speed);
}

void Object_RotateTowardsPosition(GameObject *obj, Vector2f pos, int speed) {
    PTR_NULLCHECK(obj);

    double angle;
    angle = atan2(pos.y - obj->position.y, pos.x - obj->position.x);
    angle = angle * 180.0000 / 3.14159;

    obj->angle = angle;
    // Object_Rotate(obj, angle, speed);
}
*/
#undef PTR_NULLCHECK