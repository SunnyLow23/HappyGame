#ifndef THREATS_OBJECT
#define THREATS_OBJECT

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_FRAME_NUM 8
#define THREAT_SPEED 3

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };

    enum TypeThreat
    {
        SCORPION = 10,
        SLIME = 11,
    };

    void set_x_pos(const float& xp) {x_position = xp;}
    void set_y_pos(const float& yp) {y_position = yp;}
    float get_x_pos() const {return x_position;}
    float get_y_pos() const {return y_position;}
    void SetMapXY(const int& mp_x, const int& mp_y) {mapX = mp_x; mapY = mp_y;}

    void set_clips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return widthFrame;}
    int get_height_frame() const {return heightFrame;}
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);

    void InitThreats();
    void set_type_move(const int& TypeMove) {type_move_ = TypeMove;}
    void SetAnimationPos(const int& pos_a, const int& pos_b) {animationA = pos_a, animationB = pos_b;}
    void set_input_left(const int& ipLeft) {inputType.Left = ipLeft;}
    void ImpMoveType(SDL_Renderer* screen);
    SDL_Rect GetRectFrame();

    std::vector<BulletObject*> get_bullet_list() const {return BulletList;}
    void set_bullet_list(const std::vector<BulletObject*>& bl_list) {BulletList = bl_list;}

    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);
    //void FreeThreats();
private:
    int mapX;
    int mapY;
    float x_value;
    float y_value;
    float x_position;
    float y_position;
    bool on_ground;
    int ComeBackTime;
    SDL_Rect Frame_clip[THREAT_FRAME_NUM];
    int widthFrame;
    int heightFrame;
    int Frame;

    int type_move_;
    int animationA;
    int animationB;
    Input inputType;

    std::vector<BulletObject*> BulletList;

};

#endif // THREATS_OBJECT
