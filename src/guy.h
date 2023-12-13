// vim: ts=4 sw=4 expandtab
#pragma once

// N64
//----------------------------
#include <libdragon.h>
class GuySprite
{
public:
    GuySprite();
    sprite_t* GetSprite() const;
private:
    sprite_t* mRawSprite;
};
