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
    //char name[20];
};

struct AnimClip
{
    AnimCurve* Curves;
    unsigned int CurveCount;
    unsigned int KeyCount;
    float KeyDuration;
    char name[50];
    vec4* Keys;

    vec4 getKey(const unsigned int curveIndex, float keyIndex)
    {
        keyIndex *= KeyDuration;
        int flr = (int)floor(keyIndex);
        float ratio = keyIndex - flr;
        vec4* A = &Keys[Curves[curveIndex].startIndex + flr%KeyCount*CurveCount];
        vec4* B = &Keys[Curves[curveIndex].startIndex + ((flr+1)%KeyCount)*CurveCount];
        if(Curves[curveIndex].type == Rotation)
        {
            return vec4::qslerp(*A,*B,ratio);
        }
        else
        {
            return vec4::lerp(*A,*B,ratio);
        }
        
    };
};


class Animation
{
public:
    static Animation FromNax3(const char path[]);
    AnimClip* Clips;
    unsigned int ClipCount;
};


