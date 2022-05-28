#ifndef TEXT_OBJECT
#define TEXT_OBJECT

#include "CommonFunc.h"

class TextObject
{
public:
    TextObject();
    ~TextObject();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(int type);

    void RenderText(SDL_Renderer* screen, int xp, int yp,
                    SDL_Rect* clip = NULL, double angle = 0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetWidth() const {return Width;}
    int GetHeight() const {return Height;}

    void SetText(const std::string& text) {strValue = text;}
    std::string GetText() const {return strValue;}

private:
    std::string strValue;
    SDL_Color textColor;
    SDL_Texture* Texture;
    int Width;
    int Height;

};

#endif // TEXT_OBJECT
