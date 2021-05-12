#include "Systems.h"

DE_IMPL void deccan_physics_systems_register_all(void) {
    deccan_physics_system_init_physics_body();
    deccan_physics_system_init_physics_sim();
}
