#include "Block.h"
#include "AnimationUtil.h"
#include "ConfigUtil.h"

USING_NS_CC;

Block* Block::create(bool isEdge)
{
	Block *pRet = new(std::nothrow) Block(isEdge);
	CALL_INIT();
}

Block::Block(bool isEdge) : _isEdge(isEdge)
{
	_HP = 1000.0f;
	if (isEdge)
		_neverDie = true;
	else
		_neverDie = false;
	_velocityMagnitude = 100.0f;
}

bool Block::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	this->setTag(BLOCK_TAG);

	// Set Sprite and Physics Shape
	if (_isEdge)
	{
		// Create Block
		auto block = Sprite::create("edge.png");
		_spriteVector.pushBack(block);
		this->addChild(block);
		_physicsBody->addShape(PhysicsShapeEdgeBox::create(ConfigUtil::visibleSize * 2, PHYSICSSHAPE_MATERIAL_DEFAULT, 20.0f));
	}
	else
	{
		// Create Block
		auto block = Sprite::createWithSpriteFrameName("square.png");
		_spriteVector.pushBack(block);
		this->addChild(block);
		_physicsBody->addShape(PhysicsShapeBox::create(block->getTextureRect().size, MATERIAL_BLOCK));
	}
	// Set Physics Body
	_physicsBody->setContactTestBitmask(BLOCK_CONTACT_MASK);

	return true;
}

void Block::onEnter()
{
	BaseObject::onEnter();
	auto tintTo = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
	for (auto sprite : _spriteVector)
		sprite->runAction(tintTo->clone());
	AnimationUtil::runParticleAnimation("Death.plist", this->getParent(), this);
}

void Block::onDestroy()
{
	AnimationUtil::runParticleAnimation("Death.plist", this->getParent(), this);
	BaseObject::onDestroy();
}