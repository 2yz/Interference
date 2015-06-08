#include "Block.h"
#include "ConfigUtil.h"

Block::Block()
{
}

bool Block::init()
{
    if (!BaseObject::init())
    {
        return false;
    }
    return true;
}

cocos2d::Sprite* Block::createBlock(const char* name, float PositionX, float PositionY)
{
    if (name == nullptr || PositionX > ConfigUtil::battleSceneWidth || PositionX > ConfigUtil::battleSceneWidth || PositionX < 0 || PositionY < 0)
    {
        return nullptr;
    }
    auto block = cocos2d::Sprite::createWithSpriteFrameName(name);
    auto body = cocos2d::PhysicsBody::createEdgeBox(block->getTextureRect().size);
    body->setContactTestBitmask(0xffffffff);
    block->setPhysicsBody(body);
    block->setPosition(PositionX,PositionY);
    block->setBlendFunc(cocos2d::BlendFunc::ADDITIVE);
    block->setCameraMask(1 << 1);
    return block;
}