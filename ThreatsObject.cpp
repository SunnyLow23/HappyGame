#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
    widthFrame = 0;
    heightFrame = 0;
    x_value = 0;
    y_value = 0;
    x_position = 0;
    y_position = 0;
    on_ground = true;
    ComeBackTime = 0;
    Frame = 0;

    animationA = 0;
    animationB = 0;
    inputType.Left = 0;
    type_move_ = STATIC_THREAT;
}

ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret)
    {
        widthFrame = srcrect.w/THREAT_FRAME_NUM;
        heightFrame = srcrect.h;
    }

    return ret;
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = srcrect.x;
    rect.y = srcrect.y;
    rect.w = widthFrame;
    rect.h = heightFrame;

    return rect;
}

void ThreatsObject::set_clips()
{
    if (widthFrame > 0 && heightFrame > 0)
    {
        Frame_clip[0].x = 0;
        Frame_clip[0].y = 0;
        Frame_clip[0].w = widthFrame;
        Frame_clip[0].h = heightFrame;

        Frame_clip[1].x = widthFrame;
        Frame_clip[1].y = 0;
        Frame_clip[1].w = widthFrame;
        Frame_clip[1].h = heightFrame;

        Frame_clip[2].x = 2*widthFrame;
        Frame_clip[2].y = 0;
        Frame_clip[2].w = widthFrame;
        Frame_clip[2].h = heightFrame;

        Frame_clip[3].x = 3*widthFrame;
        Frame_clip[3].y = 0;
        Frame_clip[3].w = widthFrame;
        Frame_clip[3].h = heightFrame;

        Frame_clip[4].x = 4*widthFrame;
        Frame_clip[4].y = 0;
        Frame_clip[4].w = widthFrame;
        Frame_clip[4].h = heightFrame;

        Frame_clip[5].x = 5*widthFrame;
        Frame_clip[5].y = 0;
        Frame_clip[5].w = widthFrame;
        Frame_clip[5].h = heightFrame;

        Frame_clip[6].x = 6*widthFrame;
        Frame_clip[6].y = 0;
        Frame_clip[6].w = widthFrame;
        Frame_clip[6].h = heightFrame;

        Frame_clip[7].x = 7*widthFrame;
        Frame_clip[7].y = 0;
        Frame_clip[7].w = widthFrame;
        Frame_clip[7].h = heightFrame;
    }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    ImpMoveType(des);

    if (inputType.Left == 1 || inputType.Right == 1 || (inputType.Left == 0 && inputType.Right == 0))
    {
        Frame++;
    }
    else
    {
        Frame = 0;
    }

    if (Frame >= 8)
    {
        Frame = 0;
    }

    if (ComeBackTime == 0)
    {
        srcrect.x = x_position - mapX;
        srcrect.y = y_position - mapY;
        //lấy đúng vị trí nhân vật khi map di chuyển

        SDL_Rect* current_clip = &Frame_clip[Frame];
        SDL_Rect renderQuad = {srcrect.x, srcrect.y, widthFrame, heightFrame};
        SDL_RenderCopy(des, mObject, current_clip, &renderQuad);
    }
}

void ThreatsObject::DoPlayer(Map& gMap)
{
    if (ComeBackTime == 0)
    {
        x_value = 0;
        y_value += THREAT_GRAVITY_SPEED;
        if (y_value >= THREAT_MAX_FALL_SPEED)
        {
            y_value = THREAT_MAX_FALL_SPEED;
        }

        if (inputType.Left == 1)
        {
            x_value -= THREAT_SPEED;
        }
        else if (inputType.Right == 1)
        {
            x_value += THREAT_SPEED;
        }

        CheckToMap(gMap);
    }
    else if (ComeBackTime >0)
    {
        ComeBackTime--;
        if (ComeBackTime == 0)
        {
            InitThreats();
        }
    }
}

void ThreatsObject::InitThreats()
{
    x_value = 0;
    y_value = 0;
    if (x_position > 256)
    {
        x_position -= 256;
        animationA -= 256;
        animationB -= 256;
    }
    else
    {
        x_position = 0;
    }
    y_position = 0;
    ComeBackTime = 0;
    inputType.Left = 1;
}

void ThreatsObject::RemoveBullet(const int& idx)
{
    int size = BulletList.size();
    if (size > 0 && idx < size)
    {
        BulletObject* p_bullet = BulletList.at(idx);
        BulletList.erase(BulletList.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void ThreatsObject::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check horizontal
    int height_min = heightFrame < TILE_SIZE ? heightFrame : TILE_SIZE;

    x1 = (x_position + x_value)/TILE_SIZE;
    x2 = (x_position + x_value + widthFrame - 1)/TILE_SIZE;

    y1 = (y_position)/TILE_SIZE;
    y2 = (y_position + height_min - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_value > 0) // main object is moving to right
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != STATE_HP) ||
                (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != STATE_HP))
            {
                x_position = x2*TILE_SIZE;
                x_position -= widthFrame + 1;
                x_value = 0;
            }
        }
        else if (x_value < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != STATE_HP) ||
                (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != STATE_HP))
            {
                x_position = (x1 + 1)*TILE_SIZE;
                x_value = 0;
            }

        }
    }

    //check vertical

    int width_min = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;
    x1 = (x_position)/TILE_SIZE;
    x2 = (x_position + width_min)/TILE_SIZE;

    y1 = (y_position + y_value)/TILE_SIZE;
    y2 = (y_position + y_value + heightFrame - 1)/TILE_SIZE;

    /*
        x1,y1-------x2,y1
          *           *
          *           *
          *           *
        x1,y2-------x2,y2

    */

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_value > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != STATE_HP) ||
                (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != STATE_HP))
            {
                y_position = y2*TILE_SIZE;
                y_position -= (heightFrame + 1);
                y_value = 0;

                on_ground = true;
            }
        }
        else if (y_value < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != STATE_HP) ||
                (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != STATE_HP))
            {
                y_position = (y1 + 1)*TILE_SIZE;
                y_value = 0;
            }
        }
    }

    x_position += x_value;
    y_position += y_value;

    if (x_position < 0)
    {
        x_position = 0;
    }
    else if (x_position + widthFrame > map_data.maxX)
    {
        x_position = map_data.maxX - widthFrame - 1;
    }

    if (y_position > map_data.maxY)
    {
        ComeBackTime = 60;
    }

}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if (type_move_ == STATIC_THREAT)
    {
        ;
    }
    else if (type_move_ == MOVE_IN_SPACE_THREAT)
    {
        if (on_ground == true)
        {
            if (x_position > animationB)
            {
                inputType.Left = 1;
                inputType.Right = 0;
                LoadImg("img/threats/scorpion_move_left_v1.png", screen);
            }
            else if (x_position < animationA)
            {
                inputType.Left = 0;
                inputType.Right = 1;
                LoadImg("img/threats/scorpion_move_right_v1.png", screen);
            }
        }
        else
        {
            if (inputType.Left == 1)
                LoadImg("img/threats/slime_idle_v1.png", screen);
        }
    }
}

void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if (p_bullet != NULL)
    {
        p_bullet->set_bullet_type(BulletObject::FIRE_BULLET);
        bool ret = p_bullet->LoadImgBullet(screen);

        if (ret)
        {
            p_bullet->LoadImgBullet(screen);
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->SetRect(srcrect.x + 5, y_position + 10);
            p_bullet->set_x_val(15);
            BulletList.push_back(p_bullet);
        }
    }
}

void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < BulletList.size(); i++)
    {
        BulletObject* p_bullet = BulletList.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                int bullet_fistance = srcrect.x + widthFrame - p_bullet->GetRect().x;
                if (bullet_fistance < 300 && bullet_fistance > 0)
                {
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(srcrect.x + 5, srcrect.y + 10);
            }
        }
    }
}
