// vim: ts=4 sw=4 expandtab
#include "guy.hpp"

// N64
//----------------------------
#include <libdragon.h>

// System
//----------------------------
#include <cstdlib>
#include <limits>

// External
//----------------------------
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

//----------------------------
GuySprite::GuySprite(b2World* world)
{
    // Assumes rdp init
    int fp = dfs_open("/guy.sprite");
    mRawSprite = (sprite_t*)malloc(dfs_size(fp));
    assert(dfs_read(mRawSprite, 1, dfs_size(fp), fp) >= 0);
    assert(dfs_close(fp) == 0);

    // Setup physics objects
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(160, 120);
    mBody = world->CreateBody(&def);

    // Setup the polygon shape
    b2PolygonShape guyBox;
    guyBox.SetAsBox(32.f, 32.f);
    
    b2FixtureDef fixture;
    fixture.shape = &guyBox;
    fixture.density = 2.f;
    fixture.friction = 1.f;
    mBody->CreateFixture(&fixture);
}

//----------------------------
const int GuySprite::GetCurrentAnimationOffset(uint32_t tick)
{
    if (!isAnimating)
    {
        mAnimationOffset = 0;
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
    return mAnimationOffset;
}
