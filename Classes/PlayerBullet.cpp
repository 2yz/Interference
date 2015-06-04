#include "PlayerBullet.h"
#include "ConfigUtil.h"
USING_NS_CC;

PlayerBullet::PlayerBullet(cocos2d::Vec2& velocity)
{
	this->velocity = velocity;
}

bool PlayerBullet::init()
{
	if (!BaseBullet::init())
	{
		return false;
	}
	// this->setSpriteFrame("bullet.png");
	return true;
}

bool PlayerBullet::initWithSpriteFrameName(const std::string& spriteFrameName)
{
	if (!BaseBullet::initWithSpriteFrameName(spriteFrameName))
	{
		return false;
	}
	log("Texture Rect X: %f Y: %f", this->getTextureRect().size.width, this->getTextureRect().size.height);
	physicsBody = PhysicsBody::createBox(this->getTextureRect().size);
	physicsBody->setVelocity(velocity);
	physicsBody->setRotationEnable(false);
	physicsBody->setGroup(BULLET_GROUP);
	physicsBody->setContactTestBitmask(BULLET_CONTACT_MASK);
	this->setPhysicsBody(physicsBody);
	this->setTag(BULLET_TAG);
	return true;
}

PlayerBullet* PlayerBullet::create(cocos2d::Vec2& velocity, const std::string& spriteFrameName)
{
	PlayerBullet *pRet = new(std::nothrow) PlayerBullet(velocity);
	if (pRet && pRet->initWithSpriteFrameName(spriteFrameName))
	{
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}
