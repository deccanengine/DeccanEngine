#include "asset.h"

void deccan_asset_load_texture(const char *name, const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

    img = IMG_Load(path);
    if(img == NULL) {
        deccan_error("Cannot load image", path, ": ", imgerr);
    }

    tex = SDL_CreateTextureFromSurface(deccan_get_global_engine()->renderer, img);
    SDL_FreeSurface(img);

    if(tex == NULL) {
        deccan_error("Cannot create texture", name, ": ", sdlerr);
    }

    stbds_shput(deccan_get_global_engine()->textures, name, tex);
}

SDL_Texture *deccan_asset_get_texture(const char *name) {
    deccan_Info *info = deccan_get_global_engine();
    for(int i=0; i<stbds_shlen(info->textures); i++) {
        if(!strcmp(name, info->textures[i].key)) {
            return info->textures[i].value;
        }
    }
    printf("Image not found\n");
}