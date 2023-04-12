#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    float x, y;
} vector2;

float interpolate(float a0, float a1, float w);
vector2 randomGradient(int ix, int iy);
float dotGridGradient(int ix, int iy, float x, float y);
float perlin(float x, float y);
