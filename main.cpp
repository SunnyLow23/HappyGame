#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "game_map.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerInfo.h"
#include "Geometric.h"

BaseObject BackGround;
TTF_Font *font_time = NULL;
TTF_Font *font_MENU = NULL;

bool InitData()
{
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //create window
    window_sdl = SDL_CreateWindow("HappyGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window_sdl == NULL)
        return false;
    else
    {
        screen_sdl = SDL_CreateRenderer(window_sdl, -1, SDL_RENDERER_ACCELERATED);
        if (screen_sdl == NULL)
            return false;
        else
        {
            SDL_SetRenderDrawColor(screen_sdl, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                return false;
        }

        if (TTF_Init() == -1)
            return false;
        else
        {
            font_time = TTF_OpenFont("font/dlxfont_.ttf", 15);
            font_MENU = TTF_OpenFont("font/dlxfont_.ttf", 30);
            if (font_time == NULL || font_MENU == NULL)
                return false;
        }

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
            return false;
        else
        {
            music_background = Mix_LoadMUS("sound/background_music.mp3");
            sound_bullet_sym[0] = Mix_LoadWAV("sound/sphere_bullet.wav");
            sound_bullet_sym[1] = Mix_LoadWAV("sound/big_bullet.wav");
            sound_explosion_sym[0] = Mix_LoadWAV("sound/explosion_threat.wav");
            sound_coin_sym = Mix_LoadWAV("sound/coin.wav");
            sound_player_sym[0] = Mix_LoadWAV("sound/player.wav");
            sound_player_sym[1] = Mix_LoadWAV("sound/player_jump.wav");
            sound_effect_sym[0] = Mix_LoadWAV("sound/sound_effect_1.wav");

            if (sound_bullet_sym[0] == NULL || sound_explosion_sym[0] == NULL || sound_coin_sym == NULL ||
                sound_player_sym[0] == NULL || sound_player_sym[1] == NULL || sound_effect_sym[0] == NULL ||
                sound_bullet_sym[1] == NULL || music_background == NULL)
                return false;
        }
    }
    return true;
}

bool LoadBackground()
{
    bool ret = BackGround.LoadImg("img/Background/background_v1.png", screen_sdl);
    if (ret == false)
        return false;
    return true;
}

void close()
{
    BackGround.Free();
    SDL_DestroyRenderer(screen_sdl);
    screen_sdl = NULL;
    SDL_DestroyWindow(window_sdl);
    window_sdl = NULL;
    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreatList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject *dynamic_threats = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject *p_threat = (dynamic_threats + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/threats/scorpion_idle_v1.png", screen_sdl);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(320 + i*640);
            p_threat->set_y_pos(250);

            int pos1 = p_threat->get_x_pos() - 64;
            int pos2 = p_threat->get_x_pos() + 64;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject *threats_objs = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject *p_threat = (threats_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/threats/slime_idle_v1.png", screen_sdl);
            p_threat->set_clips();
            p_threat->set_x_pos(512 + i*640);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            BulletObject *p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, screen_sdl);

            list_threats.push_back(p_threat);
        }
    }

    return list_threats;
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    bool is_quit = false;

    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;

    //Make menu game
    int ret_menu = SDLCommonFunc::ShowMenu(screen_sdl, font_MENU, "PLAY GAME", "EXIT", "img/Background/background_v2.png", sound_effect_sym, music_background);
    if (ret_menu == 1)
        is_quit = true;
again_label:
    GameMap game_map;
    game_map.LoadMap("map/map_v1.dat");
    game_map.LoadTiles(screen_sdl);

    MainObject p_player;
    p_player.LoadImg("img/player/walk_right_v2.png", screen_sdl);
    p_player.set_clips();

    PlayerInfo player_info;
    player_info.Init(screen_sdl);

    PlayerMoney player_money;
    player_money.Init(screen_sdl);
    player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);

    std::vector<ThreatsObject*> threats_list = MakeThreatList();

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImgExp("img/player/exp_v1.png", screen_sdl);
    if (!tRet) return -1;
    exp_threat.set_clip();

    ExplosionObject exp_main;
    bool mRet = exp_main.LoadImgExp("img/player/exp_v1.png", screen_sdl);
    if (!mRet) return -1;
    exp_main.set_clip();

    int num_die = 0;

    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    int mark_value = 0;

    TextObject money_game;
    money_game.SetColor(TextObject::WHITE_TEXT);

    while (!is_quit)
    {
        fps_timer.start();
        bool game_over = p_player.GetIsDie();

        while (SDL_PollEvent(&event_sdl) != 0)
        {
            if (event_sdl.type == SDL_QUIT)
                is_quit = true;

            p_player.HandelInputAction(event_sdl, screen_sdl, sound_bullet_sym);
        }

        SDL_SetRenderDrawColor(screen_sdl, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR);
        //refresh
        SDL_RenderClear(screen_sdl);

        BackGround.Render(screen_sdl, NULL);

        Map map_data = game_map.getMap();

        p_player.HandleBullet(screen_sdl);
        p_player.SetMapXY(map_data.startX, map_data.startY);
        p_player.DoPlayer(map_data, sound_coin_sym, sound_player_sym);
        p_player.Show(screen_sdl);

        game_map.SetMap(map_data);
        game_map.DrawMap(screen_sdl);

        //Draw Geometric
        GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
        ColorData color_data(0, 0, 0);
        Geometric::RenderRectangle(rectangle_size, color_data, screen_sdl);

        GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38);
        ColorData color_data2(255, 255, 255);

        Geometric::RenderOutline(outLineSize, color_data2, screen_sdl);

        player_info.Show(screen_sdl);
        player_money.Show(screen_sdl);

        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.startX, map_data.startY);
                p_threat->ImpMoveType(screen_sdl);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(screen_sdl, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(screen_sdl);

                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int jj = 0; jj < tBullet_list.size(); jj++)
                {
                    BulletObject* pt_bullet = tBullet_list.at(jj);
                    if (pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                    }
                }

                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

                if (bCol1 || bCol2 || p_player.GetIsDie())
                {
                    mark_value -= 5;
                    p_player.set_die(false);
                    for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                    {
                        int x_pos = p_player.GetRect().x + p_player.get_frame_width()*0.1;
                        int y_pos = p_player.GetRect().y - p_player.get_frame_height()*1.5;

                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.Show(screen_sdl);
                        SDL_RenderPresent(screen_sdl);
                        Mix_PlayChannel(-1, sound_player_sym[0], 0);
                    }

                    num_die++;
                    if (num_die < LIFE_NUMBER)
                    {
                        p_player.SetRect(0, 0);
                        p_player.set_comeback_time(45);
                        SDL_Delay(1000);
                        player_info.Decrease();
                        player_info.Render(screen_sdl);
                        continue;
                    }
                    else
                    {
                        p_player.set_die(true);
                    }
                }
            }
        }

        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();
        std :: vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r = 0; r < bullet_arr.size(); r++)
        {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL)
            {
                for (int t = 0; t < threats_list.size(); t++)
                {
                    ThreatsObject *obj_threat = threats_list.at(t);
                    if (obj_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                        if (bCol)
                        {
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.1;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.8;
                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(screen_sdl);
                                SDL_RenderPresent(screen_sdl);
                            }
                            if (!p_player.vBullet())
                            {
                                mark_value++;
                                p_player.RemoveBullet(r);
                            }
                            else
                            {
                                mark_value += 3;
                            }
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                            if (threats_list.size() == 0)
                                game_over = true;
                            Mix_PlayChannel(-1, sound_explosion_sym[0], 0);
                        }
                    }
                }
            }
        }

        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Mark: ");
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, screen_sdl);
        mark_game.RenderText(screen_sdl, SCREEN_WIDTH*0.5 - 50, 15);

        int money_count = p_player.GetMoneyCount();
        std::string money_str = std::to_string(money_count);

        money_game.SetText(money_str);
        money_game.LoadFromRenderText(font_time, screen_sdl);
        money_game.RenderText(screen_sdl, SCREEN_WIDTH*0.5 - 250, 15);

        //play again
        if (game_over == true)
        {
            Sleep(1000);
            int ret_menu = SDLCommonFunc::ShowMenu(screen_sdl, font_MENU, "PLAY AGAIN", "EXIT GAME", "img/Background/background_v2.png", sound_effect_sym, music_background);
            if (ret_menu == 1)
            {
                is_quit = true;
                continue;
            }
            else
            {
                is_quit = false;
                goto again_label;
            }
        }

        //update screen
        SDL_RenderPresent(screen_sdl);

        //Cap the frame rate
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; // ms

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0)
                SDL_Delay(delay_time);
        }

    }

    for (int i = 0; i < threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list.at(i);
        if (p_threat)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threats_list.clear();

    close();
    return 0;
}



