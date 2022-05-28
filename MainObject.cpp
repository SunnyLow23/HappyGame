#include "MainObject.h"

MainObject::MainObject()
{
    Frame = 0;
    x_position = 0;
    y_position = 0;
    x_value = 0;
    y_value = 0;
    widthFrame = 0;
    heightFrame = 0;
    Status = WALK_NONE_RIGHT;
    previousStatus = WALK_NONE_RIGHT;
    inputType.Left = 0;
    inputType.Right = 0;
    inputType.Jump = 0;
    on_ground = false;
    moving = false;
    mapX = 0;
    mapY = 0;
    ComeBackTime = 0;
    money_count = 10;
    is_die = false;
    v_bullet = false;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        widthFrame = srcrect.w/PLAYER_FRAME_NUM;
        heightFrame = srcrect.h;
    }

    return ret;
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = srcrect.x;
    rect.y = srcrect.y;
    rect.w = widthFrame;
    rect.h = heightFrame;

    return rect;
}

void MainObject::set_clips()
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

void MainObject::Show(SDL_Renderer* des)
{
    UpdateImagePlayer(des);

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

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[2])
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:
            Status = WALK_RIGHT;
            previousStatus = WALK_NONE_RIGHT;
            moving = true;
            inputType.Right = 1;
            inputType.Left = 0;
            UpdateImagePlayer(screen);
            break;
        case SDLK_a:
            Status = WALK_LEFT;
            previousStatus = WALK_NONE_LEFT;
            moving = true;
            inputType.Left = 1;
            inputType.Right = 0;
            UpdateImagePlayer(screen);
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:
            inputType.Right = 0;
            break;
        case SDLK_a:
            inputType.Left = 0;
            break;
        }
    }

    if (inputType.Right == 0 && inputType.Left == 0)
        {
            moving = false;
            if (previousStatus == WALK_NONE_RIGHT)
            {
                Status = WALK_NONE_RIGHT;
            }
            else if (previousStatus == WALK_NONE_LEFT)
            {
                Status = WALK_NONE_LEFT;
            }
        }

    if (events.type == SDL_KEYDOWN)
    {
        if (events.key.keysym.sym == SDLK_SPACE)
        {
            inputType.Jump = 1;
        }
        if (events.key.keysym.sym == SDLK_0)
        {
            is_die = true;
        }
    }

    if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (events.button.button == SDL_BUTTON_LEFT)
        {
            if (money_count >= 1)
            {
                DecreaseMoney(1);
                v_bullet = false;
                BulletObject* p_bullet = new BulletObject();
                p_bullet->set_bullet_type(BulletObject::SPHERE_BULLET);
                p_bullet->LoadImgBullet(screen);
                Mix_PlayChannel(-1, bullet_sound[0], 0);

                switch (Status)
                {
                case WALK_LEFT:
                    p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                    p_bullet->SetRect(this->srcrect.x + widthFrame-52, srcrect.y + heightFrame*INDEX_1);
                    break;
                case WALK_RIGHT:
                    p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                    p_bullet->SetRect(this->srcrect.x + widthFrame-12, srcrect.y + heightFrame*INDEX_1);
                    break;
                case WALK_NONE_LEFT:
                    p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                    p_bullet->SetRect(this->srcrect.x + widthFrame-52, srcrect.y + heightFrame*INDEX_1);
                    break;
                case WALK_NONE_RIGHT:
                    p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                    p_bullet->SetRect(this->srcrect.x + widthFrame-12, srcrect.y + heightFrame*INDEX_1);
                    break;
                }

                p_bullet->set_x_val(20);
                p_bullet->set_y_val(20);
                p_bullet->set_is_move(true);

                BulletList.push_back(p_bullet);
            }
        }
        else if (events.button.button == SDL_BUTTON_RIGHT)
        {
            if (money_count >= 5)
            {
                DecreaseMoney(5);
                v_bullet = true;
                BulletObject* p_bullet = new BulletObject();
                p_bullet->set_bullet_type(BulletObject::BIG_BULLET);
                p_bullet->LoadImgBullet(screen);
                Mix_PlayChannel(-1, bullet_sound[1], 0);

                switch (Status)
                {
                case WALK_LEFT:
                    p_bullet->set_bullet_status(BulletObject::LEFT);
                    p_bullet->LoadImgBullet(screen);

                    p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                    p_bullet->SetRect(this->srcrect.x + widthFrame-52, srcrect.y + heightFrame*INDEX_1);
                    break;
                case WALK_RIGHT:
                    p_bullet->set_bullet_status(BulletObject::RIGHT);
                    p_bullet->LoadImgBullet(screen);

                    p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                    p_bullet->SetRect(this->srcrect.x + widthFrame-12, srcrect.y + heightFrame*INDEX_1);
                    break;
                case WALK_NONE_LEFT:
                    p_bullet->set_bullet_status(BulletObject::LEFT);
                    p_bullet->LoadImgBullet(screen);

                    p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                    p_bullet->SetRect(this->srcrect.x + widthFrame-52, srcrect.y + heightFrame*INDEX_1);
                    break;
                case WALK_NONE_RIGHT:
                    p_bullet->set_bullet_status(BulletObject::RIGHT);
                    p_bullet->LoadImgBullet(screen);

                    p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                    p_bullet->SetRect(this->srcrect.x + widthFrame-12, srcrect.y + heightFrame*INDEX_1);
                }

                p_bullet->set_x_val(40);
                p_bullet->set_y_val(40);
                p_bullet->set_is_move(true);

                BulletList.push_back(p_bullet);
            }
        }
    }

}

void MainObject::HandleBullet(SDL_Renderer* des)
{
    for (int i = 0; i < BulletList.size(); i++)
    {
        BulletObject* p_bullet = BulletList.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else
            {
                BulletList.erase(BulletList.begin() + i);
                if (p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void MainObject::RemoveBullet(const int& idx)
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

void MainObject::DoPlayer(Map& map_data, Mix_Chunk* coin_sound, Mix_Chunk* player_sound[5])
{
    if (ComeBackTime == 0)
    {
        x_value = 0;
        y_value += GRAVITY_SPEED;

        if (y_value >= MAX_FALL_SPEED)
        {
            y_value = MAX_FALL_SPEED;
        }

        if (inputType.Left == 1)
        {
            x_value -= PLAYER_SPEED;
        }
        else if (inputType.Right == 1)
        {
            x_value += PLAYER_SPEED;
        }

        if (inputType.Jump == 1)
        {
            if (on_ground == true)
            {
                y_value = - PLAYER_JUMP_VAL;
                Mix_PlayChannel(-1, player_sound[1], 0);

            }

            on_ground = false;

            inputType.Jump = 0;
        }

        CheckToMap(map_data, coin_sound, player_sound);
        CenterEntityOnMap(map_data);
    }

    if (ComeBackTime > 0)
    {

        ComeBackTime--;
        if (ComeBackTime == 0) // reset again
        {
            on_ground = false;
            if (x_position > 256)
            {
                x_position -= 256; // 4 tile map
            }
            else
            {
                x_position = 0;
            }

            y_position = 0;
            x_value = 0;
            y_value = 0;
        }
    }
}

void MainObject::CenterEntityOnMap(Map& map_data)
//di chuyển map theo nhân vật
{
    map_data.startX = x_position - (SCREEN_WIDTH/2);
    if (map_data.startX < 0)
    {
        map_data.startX = 0;
    }
    else
        if (map_data.startX + SCREEN_WIDTH >= map_data.maxX)
        {
            map_data.startX = map_data.maxX - SCREEN_WIDTH;
        }

    map_data.startY = y_position - (SCREEN_HEIGHT/2);
    if (map_data.startY < 0)
    {
        map_data.startY = 0;
    }
    else
        if (map_data.startY + SCREEN_HEIGHT >= map_data.maxY)
        {
            map_data.startY = map_data.maxY - SCREEN_HEIGHT;
        }
}

void MainObject::CheckToMap(Map& map_data, Mix_Chunk* coin_sound, Mix_Chunk* player_sound[5])
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

            if (val1 == STATE_MONEY)
            {
                map_data.tile[y1][x2] = 0;
                Mix_PlayChannel(-1, coin_sound, 0);
                IncreaseMoney(1);
            }
            else if (val2 == STATE_MONEY)
            {
                map_data.tile[y2][x2] = 0;
                Mix_PlayChannel(-1, coin_sound, 0);
                IncreaseMoney(1);
            }
            else if (val1 != BLANK_TILE || val2 != BLANK_TILE)
            {
                x_position = x2 * TILE_SIZE;
                x_position -= widthFrame + 1;
                x_value = 0;
            }
        }
        else if (x_value < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if (val1 == STATE_MONEY)
            {
                map_data.tile[y1][x1] = 0;
                Mix_PlayChannel(-1, coin_sound, 0);
                IncreaseMoney(1);
            }
            else if (val2 == STATE_MONEY)
            {
                map_data.tile[y2][x1] = 0;
                Mix_PlayChannel(-1, coin_sound, 0);
                IncreaseMoney(1);
            }
            else if (val1 != BLANK_TILE || val2 != BLANK_TILE)
            {
                x_position = (x1 + 1) * TILE_SIZE;
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

            if (val1 == STATE_MONEY)
            {
                map_data.tile[y2][x1] = 0;
                Mix_PlayChannel(-1, coin_sound, 0);
                IncreaseMoney(1);
            }
            else if (val2 == STATE_MONEY)
            {
                map_data.tile[y2][x2] = 0;
                Mix_PlayChannel(-1, coin_sound, 0);
                IncreaseMoney(1);
            }
            else if (val1 != BLANK_TILE || val2 != BLANK_TILE)
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

            if (val1 == STATE_MONEY)
            {
                map_data.tile[y1][x1] = 0;
                Mix_PlayChannel(-1, coin_sound, 0);
                IncreaseMoney(1);
            }
            else if (val2 == STATE_MONEY)
            {
                map_data.tile[y1][x2] = 0;
                Mix_PlayChannel(-1, coin_sound, 0);
                IncreaseMoney(1);
            }
            else if (val1 != BLANK_TILE || val2 != BLANK_TILE)
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
        ComeBackTime = 45;
        set_die(true);
        Mix_PlayChannel(-1, player_sound[0], 0);
    }

}

void MainObject::IncreaseMoney(const int &value)
{
    money_count += value;
}

void MainObject::DecreaseMoney(const int &value)
{
    money_count -= value;
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
    if (on_ground == true)
    {
        switch (Status)
        {
        case WALK_LEFT:
            LoadImg("img/player/walk_left_v2.png", des);
            break;
        case WALK_RIGHT:
            LoadImg("img/player/walk_right_v2.png", des);
            break;
        case WALK_NONE_LEFT:
            LoadImg("img/player/idle_left_v1.png", des);
            break;
        case WALK_NONE_RIGHT:
            LoadImg("img/player/idle_right_v1.png", des);
            break;
        }
    }
    else
    {
        if (Status == WALK_LEFT || Status == WALK_NONE_LEFT)
        {
            LoadImg("img/player/jump_left_v2.png", des);
        }
        else if (Status == WALK_RIGHT || Status == WALK_NONE_RIGHT)
        {
            LoadImg("img/player/jump_right_v2.png", des);
        }
    }
}

void MainObject::set_die(bool die)
{
    is_die = die;
}
