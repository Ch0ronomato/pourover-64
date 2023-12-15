// vim: ts=4 sw=4 expandtab
#include "guy.h"

// N64
//----------------------------
#include <libdragon.h>

// System
//----------------------------
#include <malloc.h>
#include <limits>

//----------------------------
GuySprite::GuySprite()
{
    // Assumes rdp init
    int fp = dfs_open("/guy.sprite");
    mRawSprite = (sprite_t*)malloc(dfs_size(fp));
    assert(dfs_read(mRawSprite, 1, dfs_size(fp), fp) >= 0);
    assert(dfs_close(fp) == 0);
}

//----------------------------
sprite_t* GuySprite::GetSprite() const
{
    return mRawSprite;
}

//----------------------------
const int GuySprite::GetCurrentAnimationOffset(uint32_t tick) const
{
    if (!isAnimating)
    {
        return 0;
    }
    else if (tick > mAnimationOffset)
    {
        return ((tick - mAnimationOffset) % mFramesCount) * mFramesFiller;
    }
    else
    {
        uint32_t max = std::numeric_limits<uint32_t>::max();
        return max - (mAnimationOffset - tick);
    }
}
