#include "Geometric.h"

void Geometric::RenderRectangle(const GeometricFormat& geo_size,
                                const ColorData& color_data, SDL_Renderer* screen)
{
    SDL_Rect fill_rect = {geo_size.Left, geo_size.Top, geo_size.Width, geo_size.Height};
    SDL_SetRenderDrawColor(screen, color_data.Red, color_data.Green, color_data.Blue, 0xFF);
    SDL_RenderFillRect(screen, &fill_rect);
}

void Geometric::RenderOutline(const GeometricFormat& geo_size,
                              const ColorData& color_data, SDL_Renderer* screen)
{
    SDL_Rect outRect = {geo_size.Left, geo_size.Top, geo_size.Width, geo_size.Height};
    SDL_SetRenderDrawColor(screen, color_data.Red, color_data.Green, color_data.Blue, 0xFF);
    SDL_RenderDrawRect(screen, &outRect);
}


