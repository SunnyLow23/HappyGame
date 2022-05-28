#include "BaseObject.h"

BaseObject::BaseObject()
{
    mObject = NULL;
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = 0;
    srcrect.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    Free();
    //The final texture
    SDL_Texture *new_texture = NULL;

    //Load image
    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        //Remove background
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_R, COLOR_G, COLOR_B));

        //Create texture from surface pixels
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            //Get image dimensions
            srcrect.w = load_surface->w;
            srcrect.h = load_surface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(load_surface);
    }

    mObject = new_texture;
    return mObject;
}

void BaseObject::Render(SDL_Renderer *des, const SDL_Rect *clip)
{
    SDL_Rect renderquad = {srcrect.x, srcrect.y, srcrect.w, srcrect.h};
    SDL_RenderCopy(des, mObject, clip, &renderquad);
}

void BaseObject::Free()
{
    if (mObject != NULL)
    {
        SDL_DestroyTexture(mObject);
        mObject = NULL;
        srcrect.w = 0;
        srcrect.h = 0;
    }
}
