#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_value = 0;
    y_value = 0;
    is_move = false;
    bulletType = SPHERE_BULLET;
}

BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    switch (bulletType)
    {
    case BIG_BULLET:
        if (Status == LEFT)
        {
            ret = LoadImg("img/item/big_bullet_move_left_v1.png", des);
        }
        else if (Status == RIGHT)
        {
            ret = LoadImg("img/item/big_bullet_move_right_v1.png", des);
        }
        break;
    case FIRE_BULLET:
        ret = LoadImg("img/item/fire_bullet_v1.png", des);
        break;
    default:
        ret = LoadImg("img/item/sphere_bullet_v1.png", des);
        break;
    }

    return ret;
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (bulletDirection == DIR_RIGHT)
    {
        srcrect.x += (x_value);
        if (srcrect.x > x_border)
        {
            is_move = false;
        }
    }
    else if (bulletDirection == DIR_LEFT)
    {
        srcrect.x -= (x_value);
        if (srcrect.x < 0)
        {
            is_move = false;
        }
    }
//later version
    /*else if (bulletDirection == DIR_UP)
    {
        srcrect.y -= y_value;
        if (srcrect.y < 0)
        {
            is_move = false;
        }
    }
    else if (bulletDirection == DIR_UP_LEFT)
    {
        srcrect.x -= x_value;
        if (srcrect.x < 0)
        {
            is_move = false;
        }

        srcrect.y -= y_value;
        if (srcrect.y < 0)
        {
            is_move = false;
        }
    }
    else if (bulletDirection == DIR_UP_RIGHT)
    {
        srcrect.x += x_value;
        if (srcrect.x > x_border)
        {
            is_move = false;
        }

        srcrect.y -= y_value;
        if (srcrect.y < 0)
        {
            is_move = false;
        }
    }
    else if (bulletDirection == DIR_DOWN_LEFT)
    {
        srcrect.x -= x_value;
        if (srcrect.x < 0)
        {
            is_move = false;
        }

        srcrect.y += y_value;
        if (srcrect.y > y_border)
        {
            is_move = false;
        }
    }
    else if (bulletDirection == DIR_DOWN_RIGHT)
    {
        srcrect.x += x_value;
        if (srcrect.x > x_border)
        {
            is_move = false;
        }

        srcrect.y += y_value;
        if (srcrect.y > y_border)
        {
            is_move = false;
        }
    }*/
}
