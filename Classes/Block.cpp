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
}

bool Block::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	this->setTag(BLOCK_TAG);

	// Set Sprite and Physics Body
	if (_isEdge)
	{
		_neverDie = true;
		physicsBody->addShape(PhysicsShapeEdgeBox::create(ConfigUtil::visibleSize * 2, PHYSICSSHAPE_MATERIAL_DEFAULT, 10.0f));
	}
	else
	{
		_HP = 500.0f;
		// Create Block
		auto block = Sprite::createWithSpriteFrameName("square.png");
		spriteVector.pushBack(block);
		this->addChild(block);
		physicsBody->addShape(PhysicsShapeBox::create(block->getTextureRect().size, PhysicsMaterial(0.0f, 0.0f, 10.0f)));
	}
	physicsBody->setContactTestBitmask(BLOCK_CONTACT_MASK);

	return true;
}

void Block::onEnter()
{
	BaseObject::onEnter();
	auto tintTo = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
	for (auto sprite : spriteVector)
		sprite->runAction(tintTo->clone());
	AnimationUtil::runParticleAnimation("Cloud.plist", this->getParent(), this);
}

void Block::onDestroy()
{
	AnimationUtil::runParticleAnimation("Death.plist", this->getParent(), this);
	BaseObject::onDestroy();
}