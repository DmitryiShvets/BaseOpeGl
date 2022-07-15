//
// Created by Dmitry on 15.07.2022.
//

#ifndef BASEOPEGL_SPRITEANIMATOR_H
#define BASEOPEGL_SPRITEANIMATOR_H

#include "Sprite2D.h"

class SpriteAnimator {
public:
    SpriteAnimator(Sprite2D *sprite, double frameDurSecond, size_t frameCount, bool isLoop);

    void update(const double delta);

private:
    size_t mAnimationTime = 0;
    size_t mFrame = 0;
    Sprite2D *mSprite;
    size_t mFrameDuration;
    size_t mFrameCount;
    bool isLoop;

};


#endif //BASEOPEGL_SPRITEANIMATOR_H
