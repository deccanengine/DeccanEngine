#include "asset.h"

void _priv_Asset_load_texture(const char *name, const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

    img = IMG_Load(path);
    if(img == NULL) {
        Deccan_Log.error("Cannot load image", path, ": ", imgerr);
    }

    tex = SDL_CreateTextureFromSurface(Deccan_Core.get_global_engine()->renderer, img);
    SDL_FreeSurface(img);

    if(tex == NULL) {
        Deccan_Log.error("Cannot create texture", name, ": ", sdlerr);
    }

    stbds_shput(Deccan_Core.get_global_engine()->textures, name, tex);
}

SDL_Texture *_priv_Asset_get_texture(const char *name) {
    Deccan_Info *info = Deccan_Core.get_global_engine();
    for(int i=0; i<stbds_shlen(info->textures); i++) {
        if(!strcmp(name, info->textures[i].key)) {
            return info->textures[i].value;
        }
    }
    printf("Image not found\n");
}