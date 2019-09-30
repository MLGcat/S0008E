#include "Nax3Loader.h"
Animation Animation::FromNax3(const char path[])
{
    std::ifstream stream(path, std::ifstream::binary);
    if(stream)
    {

        Animation* ret = new Animation;

        stream.seekg(0, std::ifstream::end);
        unsigned int length = stream.tellg();
        stream.seekg(0, std::ifstream::beg);

        char* buffer = new char[length];
        stream.read(buffer, length);
        stream.close();

        char* ptr = buffer;

        Nax3Header* header = (Nax3Header*)ptr;
        ptr+=sizeof(Nax3Header);
        
        ret->Clips = new AnimClip[header->numClips];
        ret->ClipCount = header->numClips;
        
        vec4* keyStart = (vec4*)&buffer[length] - header->numKeys;

        //====CLIP====
        for(unsigned int clipIndex = 0; clipIndex < header->numClips; clipIndex++)
        {
            Nax3Clip* currClip = (Nax3Clip*)ptr;
            ptr+=sizeof(Nax3Clip);

            //====EVENT====
            for(unsigned int eventIndex = 0; eventIndex < currClip->numEvents; eventIndex++)
            {
                Nax3AnimEvent* currEvent = (Nax3AnimEvent*)ptr;
                ptr+=sizeof(Nax3AnimEvent);
            }

            ret->Clips[clipIndex].Curves = new AnimCurve[currClip->numCurves];
            AnimCurve* curveObj = ret->Clips[clipIndex].Curves;

            //====CURVE====
            for (unsigned int curveIndex = 0; curveIndex < currClip->numCurves; curveIndex++)
            {   
                Nax3Curve* currCurve = (Nax3Curve*)ptr;
                ret->Clips[clipIndex].Curves[curveIndex].type = currCurve->curveType;
                ret->Clips[clipIndex].Curves[curveIndex].startIndex = currCurve->firstKeyIndex;
                ptr+=sizeof(Nax3Curve);
            }
            
            ret->Clips[clipIndex].Keys = new vec4[currClip->numKeys];
            memcpy(ret->Clips[clipIndex].Keys, keyStart + currClip->startKeyIndex, currClip->numKeys);
            
        }
        std::cout << "[Animation] Animation loaded!" << std::endl;
        return *ret;
        
    }
    else
    {
        std::cout << "[Animation] Failed to open file!" << std::endl;
        return Animation();
    }
    
};
