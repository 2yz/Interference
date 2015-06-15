#include "Enemy.h"
#include "ConfigUtil.h"
#include "AnimationUtil.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

USING_NS_CC;

Enemy::Enemy()
{
	_HP = 500.0f;
	_neverDie = false;
	_velocityMagnitude = 400.0f;
	_linearDamping = 0.0f;
	_physicsRadius = 40.0f;
	_rotateVelocity = 100.0f;
	_beDestroyable = true;
}

bool Enemy::init()
{
	if (!BaseEnemy::init())
	{
		return false;
	}

	// Set Node Tag
	this->setTag(ENEMY_TAG);

	// Create Sprite
	auto sprite1 = Sprite::create();
	auto sprite2 = Sprite::create();
	auto sprite3 = Sprite::create();
	auto sprite4 = Sprite::create();
	sprite2->setRotation(180.0f);
	sprite4->setRotation(180.0f);
	sprite3->setScale(0.2f);
	sprite4->setScale(0.2f);
	_spriteVector.pushBack(sprite1);
	_spriteVector.pushBack(sprite2);
	_spriteVector.pushBack(sprite3);
	_spriteVector.pushBack(sprite4);
	this->addChild(sprite1);
	this->addChild(sprite2);
	this->addChild(sprite3);
	this->addChild(sprite4);
	this->setScale(0.7f);

	// Set Sprite Frame
	for (auto sprite : _spriteVector)
	{
		sprite->setSpriteFrame("square.png");
	}

	// Set Physics Shape
	_physicsBody->addShape(PhysicsShapeCircle::create(_physicsRadius, MATERIAL_PLANE));
	
	this->scheduleUpdate();

	return true;
}

void Enemy::onEnter()
{
	BaseEnemy::onEnter();
	// Set Physics Body
	_physicsBody->setGroup(ENEMY_GROUP);
	_physicsBody->setContactTestBitmask(ENEMY_CONTACT_MASK);
	_physicsBody->setCollisionBitmask(ENEMY_COLLISION_MASK);
	_physicsBody->setCategoryBitmask(ENEMY_CATEGORY_MASK);
	_physicsBody->setVelocityLimit(_velocityMagnitude);
    _physicsBody->setVelocity(Vec2(random(0.0f, 160.0f), random(0.0f, 160.0f)));
    auto tintTo = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    for (auto sprite : _spriteVector)
        sprite->runAction(tintTo->clone());
}

void Enemy::onDestroy()
{
    AnimationUtil::runParticleAnimation("Death", this->getParent(), this);
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Death.mp3",false,1.0f);
    cocos2d::experimental::AudioEngine::play2d("Death.mp3");
	BaseEnemy::onDestroy();
}

void Enemy::update(float deltaTime)
{
	BaseEnemy::update(deltaTime);
	// Sprite Rotation
	if (_spriteVector.size() == 4)
	{
		float spriteRotation = _spriteVector.at(0)->getRotation() + _rotateVelocity*deltaTime*getTimeCoefficient();
		if (spriteRotation > 360000.0f)
			spriteRotation -= 360000.0f;
		_spriteVector.at(0)->setRotation(spriteRotation);
		_spriteVector.at(1)->setRotation(180.0f - spriteRotation);
		_spriteVector.at(2)->setRotation(spriteRotation * 2.0f);
		_spriteVector.at(3)->setRotation(180.0f - spriteRotation * 2.0f);
	}
}