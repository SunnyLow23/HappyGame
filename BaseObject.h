#ifndef BASE_OBJECT
#define BASE_OBJECT

#include "CommonFunc.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int &x, const int &y)
    {
        srcrect.x = x;
        srcrect.y = y;
    }
    SDL_Rect GetRect() const {return srcrect;}
    SDL_Texture *GetObject() const {return mObject;}

    bool LoadImg(std::string path, SDL_Renderer *screen);
    void Render(SDL_Renderer *des, const SDL_Rect *clip = NULL);
    void Free();
protected:
    SDL_Texture *mObject; //lưu trữ ảnh
    SDL_Rect srcrect; //definition of a rectangle - kích thước ảnh
};

#endif // BASE_OBJECT
