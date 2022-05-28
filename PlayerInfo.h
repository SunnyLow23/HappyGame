#ifndef PLAYER_INFO
#define PLAYER_INFO

#include "CommonFunc.h"
#include "BaseObject.h"

#define LIFE_NUMBER 3

class PlayerInfo : public BaseObject
{
public:
    PlayerInfo();
    ~PlayerInfo();

    void SetNum(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void InitCrease();
    void Decrease();

private:
    int number_;
    std::vector<int> pos_list_;
};

class PlayerMoney : public BaseObject
{
public:
    PlayerMoney();
    ~PlayerMoney();

    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y) {x_position = x, y_position = y;}

private:
    int x_position;
    int y_position;
};


#endif // PLAYER_INFO
