#include "Bullet.h"
#include "ConfigUtil.h"

USING_NS_CC;

Bullet* Bullet::create(const cocos2d::Vec2& unitVelocity, int bulletParent)
{
	Bullet *pRet = new(std::nothrow) Bullet(unitVelocity, bulletParent);
	CALL_INIT();
}

Bullet::Bullet(const cocos2d::Vec2& unitVelocity, int bulletParent)
{
	_HP = 100.0f;
	_neverDie = true;
	_velocityMagnitude = 400.0f;
	_velocityVec = unitVelocity * _velocityMagnitude;
	_damage = 100.0f;
	_bulletParent = bulletParent;
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
	_physicsBody->setGroup(BULLET_GROUP);
	_physicsBody->setCategoryBitmask(BULLET_CATEGORY_MASK);
	_physicsBody->setContactTestBitmask(BULLET_CONTACT_MASK);
	_physicsBody->setCollisionBitmask(BULLET_COLLISION_MASK);
	_physicsBody->setVelocity(_velocityVec);

	return true;
}

