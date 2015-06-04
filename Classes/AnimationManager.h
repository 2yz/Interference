#ifndef AnimationManager_H_
#define AnimationManager_H_

#include "AnimationUtil.h"

USING_NS_CC;

class AnimationManager
{
public:
    
    AnimationManager();
    static bool runAnimation(const char* name, Node* parent, Node* target);

};

#endif
