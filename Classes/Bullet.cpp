#include "Bullet.h"
#include "ConfigUtil.h"
#include <SimpleAudioEngine.h>

USING_NS_CC;

Bullet* Bullet::create(int bulletParent, const cocos2d::Vec2& unitVelocity)
{
	Bullet *pRet = new(std::nothrow) Bullet(bulletParent, unitVelocity);
	CALL_INIT();
}

Bullet::Bullet(int bulletParent, const cocos2d::Vec2& unitVelocity)
{
	_HP = 100.0f;
	_velocityMagnitude = 800.0f;
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
	if (_bulletParent == kPlayerTag)
		this->setTag(kPlayerBulletTag);
	else if (_bulletParent == kEnemyTag)
		this->setTag(kEnemyBulletTag);

	// Set Sprite Texture
	auto sprite = Sprite::createWithSpriteFrameName(kBulletSpriteFrame);
	_spriteVector.pushBack(sprite);
	this->addChild(sprite);

	// Set Physics Body
	_physicsBody->addShape(PhysicsShapeBox::create(sprite->getTextureRect().size, kBulletMaterial));
	if (_bulletParent == kPlayerTag)
	{
		_physicsBody->setGroup(kPlayerBulletGroup);
		_physicsBody->setCategoryBitmask(kPlayerBulletCategoryMask);
		_physicsBody->setContactTestBitmask(kPlayerBulletContactMask);
		_physicsBody->setCollisionBitmask(kPlayerBulletCollisionMask);
	}
	else if (_bulletParent == kEnemyTag)
	{
		_physicsBody->setGroup(kEnemyBulletGroup);
		_physicsBody->setCategoryBitmask(kEnemyBulletCategoryMask);
		_physicsBody->setContactTestBitmask(kEnemyBulletContactMask);
		_physicsBody->setCollisionBitmask(kEnemyBulletCollisionMask);
	}
	_physicsBody->setVelocity(_velocityVec);
	
	return true;
}

void Bullet::initMessage()
{
	_message.putString(kNameKey, kBulletName);
	_message.putInt(kBulletParent, _bulletParent);
	if (_bulletParent == kPlayerTag)
		_message.putInt(kTagKey, kPlayerBulletTag);
	else if (_bulletParent == kEnemyTag)
		_message.putInt(kTagKey, kEnemyBulletTag);
	_message.putFloat(kDamageKey, _damage);
}
