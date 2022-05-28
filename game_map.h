#ifndef GAME_MAP
#define GAME_MAP

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 30

class TileMat: public BaseObject
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return gameMap;};
    void SetMap(Map& map_data) {gameMap = map_data;};
private:
    Map gameMap;
    TileMat tile_mat[MAX_TILES];
};

#endif // GAME_MAP
