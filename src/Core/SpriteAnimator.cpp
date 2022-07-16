//
// Created by Dmitry on 15.07.2022.
//

#include "SpriteAnimator.h"


SpriteAnimator::SpriteAnimator(Sprite2D *sprite, double frameDurSecond, size_t frameCount, bool loop) : mSprite(sprite),
                                                                                                       mFrameDuration(frameDurSecond * 1000000000),
                                                                                                       mFrameCount(frameCount), isLoop(loop) {}

void SpriteAnimator::update(unsigned long long delta) {
    mAnimationTime += delta;

    if (mAnimationTime > mFrameDuration && mFrame < mFrameCount) {

        mSprite->setCurrentFrame(++mFrame);

        mAnimationTime = 0;
    }

    if (mFrame == mFrameCount && isLoop) {
        mFrame = 0;
    }
}

