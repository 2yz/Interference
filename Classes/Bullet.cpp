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
	_neverDie = true;
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
	if (_bulletParent == PLAYER)
		this->setTag(PLAYER_BULLET_TAG);
	else if (_bulletParent == ENEMY)
		this->setTag(ENEMY_BULLET_TAG);

	// Set Sprite Texture
	auto sprite = Sprite::createWithSpriteFrameName("bullet.png");
	_spriteVector.pushBack(sprite);
	this->addChild(sprite);

	// Set Physics Body
	_physicsBody->addShape(PhysicsShapeBox::create(sprite->getTextureRect().size, MATERIAL_BULLET));
	if (_bulletParent == PLAYER)
	{
		_physicsBody->setGroup(PLAYER_BULLET_GROUP);
		_physicsBody->setCategoryBitmask(PLAYER_BULLET_CATEGORY_MASK);
		_physicsBody->setContactTestBitmask(PLAYER_BULLET_CONTACT_MASK);
		_physicsBody->setCollisionBitmask(PLAYER_BULLET_COLLISION_MASK);
	}
	else if (_bulletParent == ENEMY)
	{
		_physicsBody->setGroup(ENEMY_BULLET_GROUP);
		_physicsBody->setCategoryBitmask(ENEMY_BULLET_CATEGORY_MASK);
		_physicsBody->setContactTestBitmask(ENEMY_BULLET_CONTACT_MASK);
		_physicsBody->setCollisionBitmask(ENEMY_BULLET_COLLISION_MASK);
	}
	_physicsBody->setVelocity(_velocityVec);
	
	return true;
}

void Bullet::onEnter()
{
	BaseBullet::onEnter();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bullet.mp3", false);
}

void Bullet::initMessage()
{
	_message.putString("Name", "Bullet");
	_message.putInt("BulletParent", _bulletParent);
	if (_bulletParent == PLAYER)
		_message.putInt("Tag", PLAYER_BULLET_TAG);
	else if (_bulletParent == ENEMY)
		_message.putInt("Tag", ENEMY_BULLET_TAG);
	_message.putFloat("Damage", _damage);
}
