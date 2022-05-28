#include "TextObject.h"

TextObject::TextObject()
{
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    Texture = NULL;
}

TextObject::~TextObject()
{

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
    //Render text surface
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, strValue.c_str(), textColor);
    if (text_surface)
    {
        //Create texture from surface pixels
        Texture = SDL_CreateTextureFromSurface(screen, text_surface);

        //Get image dimensions
        Width = text_surface->w;
        Height = text_surface->h;

        //Get rid of old surface
        SDL_FreeSurface(text_surface);
    }

    return Texture != NULL;
}

void TextObject::Free()
{
    if (Texture != NULL)
    {
        SDL_DestroyTexture(Texture);
        Texture = NULL;
    }
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
}

void TextObject::SetColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        textColor = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = {255, 255, 255};
        textColor = color;
    }
    else if (type == BLACK_TEXT)
    {
        SDL_Color color = {0, 0, 0};
        textColor = color;
    }
}

void TextObject::RenderText(SDL_Renderer* screen, int xp, int yp,
                    SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */,
                    SDL_Point* center /* = NULL */,
                    SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {xp, yp, Width, Height};

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(screen, Texture, clip, &renderQuad, angle, center, flip);

}
