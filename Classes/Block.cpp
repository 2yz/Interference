#include "Block.h"
#include "AnimationUtil.h"
#include "ConfigUtil.h"
#include "AudioEngine.h"

USING_NS_CC;

Block* Block::create(bool isEdge)
{
	Block *pRet = new(std::nothrow) Block(isEdge);
	CALL_INIT();
}

Block::Block(bool isEdge) : is_edge_(isEdge), score_(300)
{
	hp_ = 1000.0f;
	velocity_magnitude_ = 100.0f;
}

bool Block::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	this->setTag(kBlockTag);

	// Set Sprite and Physics Shape
	if (is_edge_)
	{
		// Create Block
		auto block = Sprite::createWithSpriteFrameName(EDGE_SPRITE_FRAME);
		sprite_vector_.pushBack(block);
		this->addChild(block);
		physics_body_->addShape(PhysicsShapeEdgeBox::create(config::kEdgeSize + Size(200.0f, 200.0f), kBlockMaterial, 120.0f));
	}
	else
	{
		// Create Block
		auto block = Sprite::createWithSpriteFrameName(BLOCK_SPRITE_FRAME);
		sprite_vector_.pushBack(block);
		this->addChild(block);
		physics_body_->addShape(PhysicsShapeBox::create(block->getTextureRect().size, kBlockMaterial));
	}
	// Set Physics Body
	physics_body_->setContactTestBitmask(kBlockContactMask);

	return true;
}

void Block::onEnter()
{
	BaseObject::onEnter();
	if (!is_edge_)
	{
		auto tintTo = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
		for (auto sprite : sprite_vector_)
			sprite->runAction(tintTo->clone());
	}
}

void Block::onDestroy()
{
	experimental::AudioEngine::play2d(DEATH_AUDIO, false, DEATH_VOLUME);
	BaseObject::onDestroy();
}

void Block::onContact(Message& message)
{
	if (message.getInt(kTagKey) == kPlayerBulletTag && !is_edge_)
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

void Block::initMessage()
{
	message_.putString(kNameKey, kBlockName);
	message_.putInt(kTagKey, kBlockTag);
}