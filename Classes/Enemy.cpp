#include "Enemy.h"
#include "ConfigUtil.h"
#include "AnimationUtil.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

USING_NS_CC;

Enemy::Enemy()
{
	_HP = 500.0f;
	_velocityMagnitude = 400.0f;
	linear_damping_ = 0.0f;
	physics_radius_ = 30.0f;
	rotate_velocity_ = 100.0f;
	_beDestroyable = true;
	_destroyDamage = 100.0f;
	_velocityMagnitude = 300.0f;
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
		_spriteVector.pushBack(sprite);
		this->addChild(sprite);
	}
	_spriteVector.at(1)->setRotation(180.0f);
	_spriteVector.at(3)->setRotation(180.0f);
	_spriteVector.at(2)->setScale(0.6f);
	_spriteVector.at(3)->setScale(0.6f);

	// Set Sprite Frame
	for (auto sprite : _spriteVector)
	{
		sprite->setSpriteFrame(kEnemySpriteFrame);
	}

	// Set Physics Shape
	_physicsBody->addShape(PhysicsShapeCircle::create(physics_radius_, kEnemyMaterial));

	this->scheduleUpdate();

	return true;
}

void Enemy::initMessage()
{
	_message.putString(kNameKey, kEnemyName);
	_message.putInt(kTagKey, kEnemyTag);
	_message.putFloat(kDestroyDamageKey, _destroyDamage);
}

void Enemy::onEnter()
{
	BaseEnemy::onEnter();
	// Set Physics Body
	_physicsBody->setGroup(kEnemyGroup);
	_physicsBody->setContactTestBitmask(kEnemyContactMask);
	_physicsBody->setCollisionBitmask(kEnemyCollisionMask);
	_physicsBody->setCategoryBitmask(kEnemyCategoryMask);
	_physicsBody->setVelocityLimit(_velocityMagnitude);
    auto tintTo = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    for (auto sprite : _spriteVector)
        sprite->runAction(tintTo->clone());
}

void Enemy::onDestroy()
{
    AnimationUtil::runParticleAnimation("Death", this->getParent(), this);
	experimental::AudioEngine::play2d(kDeathAudio);
	BaseEnemy::onDestroy();
    
}

void Enemy::onContact(Message& message)
{
	if (message.getInt(kTagKey) == kPlayerTag && _beDestroyable)
		_HP = 0.0f;
	else if (message.getInt(kTagKey) == kPlayerBulletTag)
		_HP -= message.getFloat(kDamageKey);
	if (_HP <= 0.0f)
	{
		int* buf = new int(score_);
		EventCustom event(kScoreEvent);
		event.setUserData(buf);
		_eventDispatcher->dispatchEvent(&event);
		CC_SAFE_DELETE(buf);
		onDestroy();
	}
}

void Enemy::updateStateMachine()
{

}

void Enemy::update(float deltaTime)
{
	// Sprite Rotation
	float spriteRotation = _spriteVector.at(0)->getRotation() + rotate_velocity_*deltaTime*getTimeCoefficient();
	if (spriteRotation > 360000.0f)
		spriteRotation -= 360000.0f;
	_spriteVector.at(0)->setRotation(spriteRotation);
	_spriteVector.at(1)->setRotation(180.0f - spriteRotation);
	_spriteVector.at(2)->setRotation(spriteRotation * 2.0f);
	_spriteVector.at(3)->setRotation(180.0f - spriteRotation * 2.0f);
	BaseEnemy::update(deltaTime);
}