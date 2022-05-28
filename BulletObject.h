#ifndef BULLET_OBJECT
#define BULLET_OBJECT

#include "BaseObject.h"
#include "CommonFunc.h"

class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    enum BulletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
    };

    enum BulletType
    {
        SPHERE_BULLET = 50,
        BIG_BULLET = 51,
        FIRE_BULLET = 52,
    };

    enum BulletStatus
    {
        LEFT = 60,
        RIGHT = 61,
    };

    void set_x_val(const int& xVal) {x_value = xVal;}
    void set_y_val(const int& yVal) {y_value = yVal;}

    void set_is_move(const bool& isMove) {is_move = isMove;}
    bool get_is_move() const {return is_move;}

    void set_bullet_dir(const unsigned int& bulletDir) {bulletDirection = bulletDir;}
    unsigned int get_bullet_dir() const {return bulletDirection;}

    void set_bullet_type(const unsigned int& bullet_type) {bulletType = bullet_type;}
    unsigned int get_bullet_type() const {return bulletType;}

    void HandleMove(const int& x_border, const int& y_border);
    bool LoadImgBullet(SDL_Renderer* des);

    void set_bullet_status(const int& bulletStatus) {Status = bulletStatus;}

private:
    int x_value;
    int y_value;
    bool is_move;
    unsigned int bulletDirection;
    unsigned int bulletType;
    int Status;

};

#endif // BULLET_OBJECT
