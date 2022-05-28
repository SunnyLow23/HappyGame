#ifndef EXPLOSION
#define EXPLOSION

#include "CommonFunc.h"
#include "BaseObject.h"

#define NUM_FRAME_EXP 8

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void set_clip();
    void set_frame(const int& fr) {Frame = fr;}
    virtual bool LoadImgExp(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const {return widthFrame;}
    int get_frame_height() const {return heightFrame;}

private:
    int widthFrame;
    int heightFrame;

    unsigned int Frame;
    SDL_Rect Frame_clip[8];

};

#endif // EXPLOSION
