#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
    heightFrame = 0;
    widthFrame = 0;
    Frame = 0;
}

ExplosionObject::~ExplosionObject()
{

}

bool ExplosionObject::LoadImgExp(std::string path, SDL_Renderer* screen)
{
    bool ret = ExplosionObject::LoadImg(path, screen);

    if (ret)
    {
        widthFrame = srcrect.w/NUM_FRAME_EXP;
        heightFrame = srcrect.h;
    }

    return ret;
}

void ExplosionObject::set_clip()
{
    if (widthFrame > 0 && heightFrame > 0)
    {
        Frame_clip[0].x = 0;
        Frame_clip[0].y = 0;
        Frame_clip[0].w = widthFrame;
        Frame_clip[0].h = heightFrame;

        Frame_clip[1].x = widthFrame*1;
        Frame_clip[1].y = 0;
        Frame_clip[1].w = widthFrame;
        Frame_clip[1].h = heightFrame;

        Frame_clip[2].x = widthFrame*2;
        Frame_clip[2].y = 0;
        Frame_clip[2].w = widthFrame;
        Frame_clip[2].h = heightFrame;

        Frame_clip[3].x = widthFrame*3;
        Frame_clip[3].y = 0;
        Frame_clip[3].w = widthFrame;
        Frame_clip[3].h = heightFrame;

        Frame_clip[4].x = widthFrame*4;
        Frame_clip[4].y = 0;
        Frame_clip[4].w = widthFrame;
        Frame_clip[4].h = heightFrame;

        Frame_clip[5].x = widthFrame*5;
        Frame_clip[5].y = 0;
        Frame_clip[5].w = widthFrame;
        Frame_clip[5].h = heightFrame;

        Frame_clip[6].x = widthFrame*6;
        Frame_clip[6].y = 0;
        Frame_clip[6].w = widthFrame;
        Frame_clip[6].h = heightFrame;

        Frame_clip[7].x = widthFrame*7;
        Frame_clip[7].y = 0;
        Frame_clip[7].w = widthFrame;
        Frame_clip[7].h = heightFrame;
    }
}

void ExplosionObject::Show(SDL_Renderer* screen)
{
    SDL_Rect* current_clip = &Frame_clip[Frame];
    SDL_Rect render_quad = {srcrect.x, srcrect.y, widthFrame, heightFrame};
    if (current_clip != NULL)
    {
        render_quad.w = current_clip->w;
        render_quad.h = current_clip->h;
    }

    SDL_RenderCopy(screen, mObject, current_clip, &render_quad);
}
