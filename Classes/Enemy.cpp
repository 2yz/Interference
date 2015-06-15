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
	linear_damping_ = 0.0f;
	physics_radius_ = 40.0f;
	rotate_velocity_ = 100.0f;
	_beDestroyable = true;
	_destroyDamage = 100.0f;
	_velocityMagnitude = 300.0f;
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
	sprite3->setScale(0.6f);
	sprite4->setScale(0.6f);
	_spriteVector.pushBack(sprite1);
	_spriteVector.pushBack(sprite2);
	_spriteVector.pushBack(sprite3);
	_spriteVector.pushBack(sprite4);
	this->addChild(sprite1);
	this->addChild(sprite2);
	this->addChild(sprite3);
	this->addChild(sprite4);

	// Set Sprite Frame
	for (auto sprite : _spriteVector)
	{
		sprite->setSpriteFrame(ENEMY_SPRITE_FRAME);
	}

	// Set Physics Shape
	_physicsBody->addShape(PhysicsShapeCircle::create(physics_radius_, MATERIAL_ENEMY_PLANE));

	this->scheduleUpdate();

	return true;
}

void Enemy::initMessage()
{
	_message.putString("Name", "Enemy");
	_message.putInt("Tag", ENEMY_TAG);
	_message.putFloat("DestroyDamage", _destroyDamage);
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
    cocos2d::experimental::AudioEngine::play2d("Death.mp3");
	BaseEnemy::onDestroy();
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