#include "Drawable.h"
#include "../../Scene/Flecs.h"

void DE_CompDrawableRegister(void) {
    DE_FlecsRegisterComponent("Drawable", sizeof(DeccanCompDrawable), ECS_ALIGNOF(DeccanCompDrawable));
}
