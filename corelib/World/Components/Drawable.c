#include "Drawable.h"
#include "../Flecs.h"

void DE_CompDrawableRegister(void) {
    DE_FlecsRegisterComponent("Drawable", sizeof(DeccanCompDrawable), ECS_ALIGNOF(DeccanCompDrawable));
}
