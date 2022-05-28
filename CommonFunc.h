#ifndef COMMON_FUNCTION
#define COMMON_FUNCTION

#include <windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "BaseObject.h"
#include "TextObject.h"

static SDL_Window *window_sdl = NULL;
static SDL_Renderer *screen_sdl = NULL;
static SDL_Event event_sdl;

//audio
static Mix_Chunk *sound_bullet_sym[2];
static Mix_Chunk *sound_explosion_sym[2];
static Mix_Chunk *sound_coin_sym = NULL;
static Mix_Chunk *sound_player_sym[5];
static Mix_Chunk *sound_effect_sym[3];
static Mix_Music *music_background = NULL;

//Screen
const int FRAME_PER_SECOND = 23;    //fps

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 640;

const int COLOR_R = 0;
const int COLOR_G = 0;
const int COLOR_B = 0;
const int DEFAULT_COLOR = 0;

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 200
#define MAX_MAP_Y 10

#define STATE_MONEY 16
#define STATE_HP 15

struct Input
{
    int Left;
    int Right;
    int Jump;
};

struct Map
{
    int startX;
    int startY;

    int maxX;
    int maxY;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char *FileName;

};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect &object1, const SDL_Rect &object2);
    int ShowMenu(SDL_Renderer *screen_sdl, TTF_Font *font,
                 const std::string &menu1,
                 const std::string &menu2,
                 const std::string &img_name,
                 Mix_Chunk *effect_sound[3], Mix_Music *background_music);
}

#endif // COMMON_FUNCTION
