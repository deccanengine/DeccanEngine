#pragma once
#include "../config.h"
#include "scene.h"

typedef struct Deccan_GameObject Deccan_GameObject;
typedef struct Deccan_GameObject {
    char *name, *type;
    int32_t x, y;
    bool dead, hidden;

    void (*at_beginning)(Deccan_GameObject *object);
    void (*at_step)(Deccan_GameObject *object);
    void (*at_end)(Deccan_GameObject *object);
} Deccan_GameObject;

Deccan_GameObject *_priv_Object_new_object(const char *name, const char *type, void (*ab)(Deccan_GameObject *object), 
    void (*as)(Deccan_GameObject *object), void (*ae)(Deccan_GameObject *object));
void _priv_Object_instantiate_object(Deccan_GameObject *object);

typedef struct _priv_Object {
    Deccan_GameObject *(*new_object)(const char *name, const char *type, void (*ab)(Deccan_GameObject *object), 
        void (*as)(Deccan_GameObject *object), void (*ae)(Deccan_GameObject *object));
    void (*instantiate_object)(Deccan_GameObject *object);
} _priv_Object;

static _priv_Object Deccan_Object = { 
    _priv_Object_new_object,
    _priv_Object_instantiate_object 
};