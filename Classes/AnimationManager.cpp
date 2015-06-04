#include "AnimationManager.h"


bool AnimationManager::runAnimation(const char* name, Node* parent, Node* target)
{
    if (parent == nullptr || target == nullptr)
    {
        return false;
    }
    Sprite* runSp = Sprite::create();
    runSp->setPosition(target->getPosition());
    parent->addChild(runSp);
    runSp->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(name)));
    return true;
}