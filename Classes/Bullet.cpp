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
	hp_ = 100.0f;
	velocity_magnitude_ = 800.0f;
	velocity_vec_ = unitVelocity * velocity_magnitude_;
	damage_ = 100.0f;
	bullet_parent_ = bulletParent;
}

bool Bullet::init()
{
	if (!BaseBullet::init())
	{
		return false;
	}
	
	// Set Node Tag
	if (bullet_parent_ == kPlayerTag)
		this->setTag(kPlayerBulletTag);
	else if (bullet_parent_ == kEnemyTag)
		this->setTag(kEnemyBulletTag);

	// Set Sprite Texture
	auto sprite = Sprite::createWithSpriteFrameName(BULLET_SPRITE_FRAME);
	sprite_vector_.pushBack(sprite);
	this->addChild(sprite);

	// Set Physics Body
	physics_body_->addShape(PhysicsShapeBox::create(sprite->getTextureRect().size, kBulletMaterial));
	if (bullet_parent_ == kPlayerTag)
	{
		physics_body_->setGroup(kPlayerBulletGroup);
		physics_body_->setCategoryBitmask(kPlayerBulletCategoryMask);
		physics_body_->setContactTestBitmask(kPlayerBulletContactMask);
		physics_body_->setCollisionBitmask(kPlayerBulletCollisionMask);
	}
	else if (bullet_parent_ == kEnemyTag)
	{
		physics_body_->setGroup(kEnemyBulletGroup);
		physics_body_->setCategoryBitmask(kEnemyBulletCategoryMask);
		physics_body_->setContactTestBitmask(kEnemyBulletContactMask);
		physics_body_->setCollisionBitmask(kEnemyBulletCollisionMask);
	}
	physics_body_->setVelocity(velocity_vec_);
	
	return true;
}

void Bullet::initMessage()
{
	message_.putString(kNameKey, kBulletName);
	message_.putInt(kBulletParent, bullet_parent_);
	if (bullet_parent_ == kPlayerTag)
		message_.putInt(kTagKey, kPlayerBulletTag);
	else if (bullet_parent_ == kEnemyTag)
		message_.putInt(kTagKey, kEnemyBulletTag);
	message_.putFloat(kDamageKey, damage_);
}
