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

Block::Block(bool isEdge) : _isEdge(isEdge), score_(300)
{
	hp_ = 1000.0f;
	_velocityMagnitude = 100.0f;
}

bool Block::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	this->setTag(kBlockTag);

	// Set Sprite and Physics Shape
	if (_isEdge)
	{
		// Create Block
		auto block = Sprite::createWithSpriteFrameName(kEdgeSpriteFrame);
		_spriteVector.pushBack(block);
		this->addChild(block);
		_physicsBody->addShape(PhysicsShapeEdgeBox::create(config::kEdgeSize + Size(200.0f, 200.0f), kBlockMaterial, 120.0f));
	}
	else
	{
		// Create Block
		auto block = Sprite::createWithSpriteFrameName(kBlockSpriteFrame);
		_spriteVector.pushBack(block);
		this->addChild(block);
		_physicsBody->addShape(PhysicsShapeBox::create(block->getTextureRect().size, kBlockMaterial));
	}
	// Set Physics Body
	_physicsBody->setContactTestBitmask(kBlockContactMask);

	return true;
}

void Block::onEnter()
{
	BaseObject::onEnter();
	if (!_isEdge)
	{
		auto tintTo = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
		for (auto sprite : _spriteVector)
			sprite->runAction(tintTo->clone());
	}
}

void Block::onDestroy()
{
	experimental::AudioEngine::play2d(kDeathAudio, false, kDeathVolume);
	BaseObject::onDestroy();
}

void Block::onContact(Message& message)
{
	if (message.getInt(kTagKey) == kPlayerBulletTag && !_isEdge)
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
	_message.putString(kNameKey, kBlockName);
	_message.putInt(kTagKey, kBlockTag);
}