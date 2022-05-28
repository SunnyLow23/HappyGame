#ifndef GEOMETRIC
#define GEOMETRIC

#include "CommonFunc.h"

typedef struct GeometricFormat
{
public:
    GeometricFormat(int left, int top, int width, int height)
        {Left = left, Top = top, Width = width, Height = height;};

    int Left;
    int Top;
    int Width;
    int Height;
};

typedef struct ColorData
{
    ColorData(Uint8 r, Uint8 g, Uint8 b) {Red = r, Green = g, Blue = b;}
public:
    Uint8 Red;
    Uint8 Green;
    Uint8 Blue;
};

class Geometric
{
public:
    static void RenderRectangle(const GeometricFormat& geo_size,
                                const ColorData& color_data, SDL_Renderer* screen);
    static void RenderOutline(const GeometricFormat& geo_size,
                              const ColorData& color_data, SDL_Renderer* screen);
};

#endif // GEOMETRIC
