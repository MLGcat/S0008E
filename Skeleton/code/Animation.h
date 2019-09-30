#pragma once
#include <iostream>
#include <fstream>
#include "Nax3Structs.h"
#include "Math4D.h"
#include <cstring>

enum Curvetype
{
    Translation,
    Scale,
    Rotation,
    Color,
    Velocity
};

struct AnimCurve
{
    unsigned int type;
    unsigned int startIndex;
};

struct AnimClip
{
    AnimCurve* Curves;
    unsigned int CurveCount;
    char name[50];
    vec4* Keys;
};


class Animation
{
public:
    static Animation FromNax3(const char path[]);
    AnimClip* Clips;
    unsigned int ClipCount;
};


