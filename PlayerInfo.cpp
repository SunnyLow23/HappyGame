#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
{
    number_ = 0;
}

PlayerInfo::~PlayerInfo()
{

}

void PlayerInfo::AddPos(const int& xp)
{
    pos_list_.push_back(xp);
}

void PlayerInfo::Init(SDL_Renderer* screen)
{
    LoadImg("img/player/player_life.png", screen);
    number_ = LIFE_NUMBER;
    if (pos_list_.size() > 0)
    {
        pos_list_.clear();
    }

    for (int i = 0; i < LIFE_NUMBER; i++)
    {
        AddPos(20 + 40*i);
    }
}

void PlayerInfo::Show(SDL_Renderer* screen)
{
    for (int i = 0; i < pos_list_.size(); i++)
    {
        srcrect.x = pos_list_.at(i);
        srcrect.y = 0;
        Render(screen);
    }
}

void PlayerInfo::Decrease()
{
    number_--;
    pos_list_.pop_back();
}

void PlayerInfo::InitCrease()
{
    number_++;
    int last_pos = pos_list_.back();
    last_pos += 40;
    pos_list_.push_back(last_pos);
}

PlayerMoney::PlayerMoney()
{
    x_position = 0;
    y_position = 0;
}

PlayerMoney::~PlayerMoney()
{

}

void PlayerMoney::Init(SDL_Renderer* screen)
{
    bool ret = LoadImg("img/player/coin.png", screen);
}

void PlayerMoney::Show(SDL_Renderer* screen)
{
    srcrect.x = x_position;
    srcrect.y = y_position;
    Render(screen);
}
