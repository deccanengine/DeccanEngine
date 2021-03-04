#include "Components.h"

void DE_RenderComponentsRegisterAll(void) {
    DE_CompDrawableRegister();
    DE_CompDrawableGeometryRegister();
}
