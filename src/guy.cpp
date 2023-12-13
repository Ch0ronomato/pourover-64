// vim: ts=4 sw=4 expandtab
#include "guy.h"

// N64
//----------------------------
#include <libdragon.h>

// System
//----------------------------
#include <malloc.h>

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
