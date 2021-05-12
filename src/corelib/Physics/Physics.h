#pragma once
#include "../Config.h"
#include "../Core/Module/Module.h"

DE_API void deccan_physics_init(void);
DE_API void deccan_physics_quit(void);
DE_API void deccan_physics_step(void);

DE_API cpSpace *deccan_physics_get_space(void);
DE_API deccan_module_t *deccan_physics_module(void);
