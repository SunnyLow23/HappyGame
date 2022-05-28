#include"game_map.h"

void GameMap::LoadMap(char* name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if (fp == NULL)
        return;

    gameMap.maxX = 0;
    gameMap.maxY = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf_s(fp, "%d", &gameMap.tile[i][j]);
            int val = gameMap.tile[i][j];
            if (val > 0)
            {
                if (j > gameMap.maxX)
                    gameMap.maxX = j;
                if (i > gameMap.maxY)
                    gameMap.maxY = i;
            }
        }
    }
    gameMap.maxX = (gameMap.maxX + 1)*TILE_SIZE;
    gameMap.maxY = (gameMap.maxY + 1)*TILE_SIZE;
    gameMap.startX = 0;
    gameMap.startY = 0;

    gameMap.FileName = name;
    fclose(fp);

}
void GameMap::LoadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    FILE *fp = NULL;
    for (int i = 0; i < MAX_TILES; i++)
    {
        sprintf_s(file_img, "map/%d.png", i);
        fopen_s(&fp, file_img, "rb");
        if (fp == NULL)
            continue;

        fclose(fp);
        tile_mat[i].LoadImg(file_img, screen);
    }
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = gameMap.startX/TILE_SIZE;
    x1 = (gameMap.startX%TILE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = gameMap.startY/TILE_SIZE;
    y1 = (gameMap.startY%TILE_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i+= TILE_SIZE)
    {
        map_x = gameMap.startX/TILE_SIZE;
        for (int j = x1; j < x2; j+= TILE_SIZE)
        {
            int val = gameMap.tile[map_y][map_x];
            if (val > 0)
            {
                tile_mat[val].SetRect(j, i);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
