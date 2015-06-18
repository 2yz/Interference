#include "MouseLayer.h"
#include "Controller.h"
#include "ConfigUtil.h"

USING_NS_CC;

MouseLayer::MouseLayer()
{
}

bool MouseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	mouseSprite = Sprite::createWithSpriteFrameName(kShootBoxSpriteFrame);
	mouseSprite->setBlendFunc(BlendFunc::ADDITIVE);
	this->addChild(mouseSprite);
	this->scheduleUpdate();
	return true;
}

void MouseLayer::update(float deltaTime)
{
	mouseSprite->setPosition(Controller::getMouseLocation());
	if (Controller::getMouseDown())
	{
		auto scaleToSmall = ScaleTo::create(0.1f, 0.6f);
		auto scaleToBig = ScaleTo::create(0.1f, 1.0f);
		mouseSprite->runAction(Sequence::create(scaleToSmall, scaleToBig, nullptr));
	}
}