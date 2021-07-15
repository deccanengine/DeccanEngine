/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/core/string.h>
#include <deccanengine/core/core.h>
#include <deccanengine/core/utils.h>

DE_IMPL char *deccan_string_new(const char *source) {
    size_t len = strlen(source);
    char *string = deccan_alloc(sizeof(char), len + 1);

    strncpy(string, source, len);
    string[len] = '\0';
    return string;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL uint32_t deccan_string_hash(const char *string, int length) {
    return zpl_adler32((const void *)string, length);
}
