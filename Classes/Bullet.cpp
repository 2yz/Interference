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
	_spriteVector.pushBack(sprite);
	this->addChild(sprite);

	// Set Physics Body
	_physicsBody->addShape(PhysicsShapeBox::create(sprite->getTextureRect().size, MATERIAL_BULLET));
	_physicsBody->setVelocity(velocityVec);
	_physicsBody->setGroup(BULLET_GROUP);
	_physicsBody->setContactTestBitmask(BULLET_CONTACT_MASK);
	_physicsBody->setCollisionBitmask(BULLET_COLLISION_MASK);
	_physicsBody->setCategoryBitmask(BULLET_CATEGORY_MASK);

	return true;
}

