// vim: ts=4 sw=4 expandtab
#pragma once

// N64
//----------------------------
#include <libdragon.h>
namespace
{
    static uint32_t kGuySpriteFramesCount = 8;
    static uint32_t kGuySpriteFiller = 2;
}

class GuySprite
{
public:
    GuySprite();
    sprite_t* GetSprite() const;
    const int GetCurrentAnimationOffset(uint32_t tick);
    void Animate(bool state) { isAnimating = state; };
private:
    // Sprite data
    sprite_t* mRawSprite;

    // Animation state
    uint32_t mAnimationOffset = 0;
    bool isAnimating = false;

    uint32_t mFramesCount = kGuySpriteFramesCount;
    uint32_t mFramesFiller = kGuySpriteFiller;
};
