#include "Enemy.h"
#include "ConfigUtil.h"
#include "AnimationUtil.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

USING_NS_CC;

Enemy::Enemy()
{
	hp_ = 200.0f;
	velocity_magnitude_ = 400.0f;
	linear_damping_ = 0.0f;
	physics_radius_ = 30.0f;
	rotate_velocity_ = 100.0f;
	be_destroyable_ = true;
	destroy_damage_ = 100.0f;
	velocity_magnitude_ = 300.0f;
	score_ = 50;
}

bool Enemy::init()
{
	if (!BaseEnemy::init())
	{
		return false;
	}

	// Set Node Tag
	this->setTag(kEnemyTag);

	// Create Sprite
	for (int i = 0; i < 4; ++i)
	{
		auto sprite = Sprite::create();
		sprite_vector_.pushBack(sprite);
		this->addChild(sprite);
	}
	sprite_vector_.at(1)->setRotation(180.0f);
	sprite_vector_.at(3)->setRotation(180.0f);
	sprite_vector_.at(2)->setScale(0.6f);
	sprite_vector_.at(3)->setScale(0.6f);

	// Set Sprite Frame
	for (auto sprite : sprite_vector_)
	{
		sprite->setSpriteFrame(ENEMY_SPRITE_FRAME);
	}

	// Set Physics Shape
	physics_body_->addShape(PhysicsShapeCircle::create(physics_radius_, kEnemyMaterial));

	this->scheduleUpdate();

	return true;
}

void Enemy::initMessage()
{
	message_.putString(kNameKey, kEnemyName);
	message_.putInt(kTagKey, kEnemyTag);
	message_.putFloat(kDestroyDamageKey, destroy_damage_);
}

void Enemy::onEnter()
{
	BaseEnemy::onEnter();
	// Set Physics Body
	physics_body_->setGroup(kEnemyGroup);
	physics_body_->setContactTestBitmask(kEnemyContactMask);
	physics_body_->setCollisionBitmask(kEnemyCollisionMask);
	physics_body_->setCategoryBitmask(kEnemyCategoryMask);
	physics_body_->setVelocityLimit(velocity_magnitude_);
    auto tintTo = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    for (auto sprite : sprite_vector_)
        sprite->runAction(tintTo->clone());
	AnimationUtil::runParticleAnimation(BIRTH_PARTICLE, this->getParent(), this);
}

void Enemy::onDestroy()
{
	AnimationUtil::runParticleAnimation(DEATH_PARTICLE, this->getParent(), this);
	experimental::AudioEngine::play2d(DEATH_AUDIO);
	BaseEnemy::onDestroy();
    
}

void Enemy::onContact(Message& message)
{
	if (message.getInt(kTagKey) == kPlayerTag && be_destroyable_)
		hp_ = 0.0f;
	else if (message.getInt(kTagKey) == kPlayerBulletTag)
		hp_ -= message.getFloat(kDamageKey);
	if (hp_ <= 0.0f)
	{
		int* buf = new int(score_);
		EventCustom event(SCORE_EVENT);
		event.setUserData(buf);
		_eventDispatcher->dispatchEvent(&event);
		CC_SAFE_DELETE(buf);
		onDestroy();
	}
}

void Enemy::update(float delta_time)
{
	delta_time *= getTimeCoefficient();
	BaseEnemy::update(delta_time);
	updateStateMachine(delta_time);
	// Sprite Rotation
	float spriteRotation = sprite_vector_.at(0)->getRotation() + rotate_velocity_*delta_time;
	if (spriteRotation > 360000.0f)
		spriteRotation -= 360000.0f;
	sprite_vector_.at(0)->setRotation(spriteRotation);
	sprite_vector_.at(1)->setRotation(180.0f - spriteRotation);
	sprite_vector_.at(2)->setRotation(spriteRotation * 2.0f);
	sprite_vector_.at(3)->setRotation(180.0f - spriteRotation * 2.0f);
}

void Enemy::updateStateMachine(float delta_time)
{
}

void Enemy::setState(EnemyState battle_state)
{
}

void Enemy::enterState(EnemyState battle_state)
{
}

void Enemy::exitState()
{
}