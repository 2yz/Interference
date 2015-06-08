#include "Bullet.h"
#include "ConfigUtil.h"

USING_NS_CC;

Bullet* Bullet::create(const cocos2d::Vec2& velocity)
{
	Bullet *pRet = new(std::nothrow) Bullet(velocity);
	CALL_INIT();
}

Bullet::Bullet(const cocos2d::Vec2& velocity)
{
	velocityVec = velocity;
}

bool Bullet::init()
{
	if (!BaseBullet::init())
	{
		return false;
	}
	
	// Set Node Tag
	this->setTag(BULLET_TAG);

	// Set Sprite Texture
	auto sprite = Sprite::createWithSpriteFrameName("bullet.png");
	spriteVector.pushBack(sprite);
	this->addChild(sprite);

	// Set Physics Body
	physicsBody->addShape(PhysicsShapeBox::create(sprite->getTextureRect().size));
	physicsBody->setVelocity(velocityVec);
	physicsBody->setGroup(BULLET_GROUP);
	physicsBody->setContactTestBitmask(BULLET_CONTACT_MASK);
	physicsBody->setCollisionBitmask(BULLET_COLLISION_MASK);
	physicsBody->setCategoryBitmask(BULLET_CATEGORY_MASK);

	return true;
}

