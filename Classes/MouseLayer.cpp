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
	mouse_sprite_ = Sprite::createWithSpriteFrameName(SHOOT_BOX_SPRITE_FRAME);
	mouse_sprite_->setBlendFunc(BlendFunc::ADDITIVE);
	this->addChild(mouse_sprite_);
	this->scheduleUpdate();
	return true;
}

void MouseLayer::update(float delta_time)
{
	mouse_sprite_->setPosition(Controller::getMouseLocation());
	if (Controller::getMouseDown())
	{
		auto scaleToSmall = ScaleTo::create(0.1f, 0.7f);
		auto scaleToBig = ScaleTo::create(0.1f, 1.0f);
		mouse_sprite_->runAction(Sequence::create(scaleToSmall, scaleToBig, nullptr));
	}
}