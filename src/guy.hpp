// vim: ts=4 sw=4 expandtab
#pragma once

// N64
//----------------------------
#include <libdragon.h>

class b2Body;
class b2World;

class GuySprite
{
public:
    GuySprite(b2World* world);
    sprite_t* GetSprite() const { return mRawSprite; };
    const b2Body* GetBody() const { return mBody; };
    const int GetCurrentAnimationOffset(uint32_t tick);
    void Animate(bool state) { isAnimating = state; };
private:
    // Sprite data
    sprite_t* mRawSprite;

    // Animation state
    uint32_t mAnimationOffset = 0;
    bool isAnimating = false;

    // animation filler
    uint32_t mFramesCount = 8;
    uint32_t mFramesFiller = 2;

    // physics properties
    b2Body* mBody;
};
