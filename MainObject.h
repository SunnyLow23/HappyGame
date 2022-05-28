#ifndef MAIN_OBJECT
#define MAIN_OBJECT

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 15
#define PLAYER_FRAME_NUM 8
#define INDEX_1 0.45

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_NONE_RIGHT = 1,
        WALK_NONE_LEFT = 2,
        WALK_RIGHT = 3,
        WALK_LEFT = 4,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[2]);
    void set_clips();

    int get_frame_width() const {return widthFrame;}
    int get_frame_height() const {return heightFrame;}

    void DoPlayer(Map& map_data, Mix_Chunk* coin_sound, Mix_Chunk* player_sound[5]);
    void CheckToMap(Map& map_data, Mix_Chunk* coin_sound, Mix_Chunk* player_sound[5]);
    void SetMapXY(const int map_x, const int map_y) {mapX = map_x; mapY = map_y;}
    void CenterEntityOnMap(Map& map_data);
    void UpdateImagePlayer(SDL_Renderer* des);
    SDL_Rect GetRectFrame();

    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        BulletList = bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list() const {return BulletList;}
    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int& idx);

    void IncreaseMoney(const int &value);
    void DecreaseMoney(const int &value);
    int GetMoneyCount() const {return money_count;}

    void set_comeback_time(const int& cb_time) {ComeBackTime = cb_time;}
    void set_die(bool die);
    bool GetIsDie() const {return is_die;}
    bool vBullet() const {return v_bullet;}
private:
    int money_count;
    int ComeBackTime;

    std::vector<BulletObject*> BulletList;

    float x_value;
    float y_value;
    float x_position;
    float y_position;

    int widthFrame;
    int heightFrame;
    SDL_Rect Frame_clip[PLAYER_FRAME_NUM];
    Input inputType;
    int Frame;
    int Status;
    int previousStatus;

    int mapX;
    int mapY;

    bool on_ground;
    bool moving;
    bool is_die;
    bool v_bullet;
};

#endif // MAIN_OBJECT

