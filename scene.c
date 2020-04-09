#include "scene.h"

deccan_scene *deccan_new_scene(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae)) {
    deccan_scene *scene = malloc(sizeof(deccan_scene));
    scene->at_begining = as;
    scene->at_step = as;
    scene->at_end = ae;
    return scene;
}