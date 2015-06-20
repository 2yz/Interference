#include "MenuLayer.h"
#include "ConfigUtil.h"
#include "BattleScene.h"

USING_NS_CC;

MenuLayer::MenuLayer()
{
}

bool MenuLayer::init()
{
	if (!Layer::init())
		return false;
	logo_ = Sprite::createWithSpriteFrameName(LOGO_SPRITE_FRAME);
	logo_->setPosition(config::visible_width - 360.0f, config::visible_height / 2);
	this->addChild(logo_);
	background_ = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(MENU_BACKGROUND_TEXTURE));
	background_->setPosition(config::visible_size / 2);
	this->addChild(background_);
	start_button_ = ui::Button::create(START_BUTTON_TEXTURE, START_BUTTON_TEXTURE, START_BUTTON_TEXTURE);
	start_button_->setPosition(Vec2(240.0f, config::visible_height / 2 + 40.0f));
	start_button_->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			for (auto child : _children)
				child->runAction(FadeOut::create(0.5f));
			BattleScene::getInstance()->startBattle();
			scheduleOnce(schedule_selector(MenuLayer::exitSchedule), 0.6f);
			break;
		default:
			break;
		}
	});
	this->addChild(start_button_);
	exit_button_ = ui::Button::create(EXIT_BUTTON_TEXTURE, EXIT_BUTTON_TEXTURE, EXIT_BUTTON_TEXTURE);
	exit_button_->setPosition(Vec2(240.0f, config::visible_height / 2 - 40.0f));
	exit_button_->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	});
	this->addChild(exit_button_);
	return true;
}

void MenuLayer::onEnter()
{
	Layer::onEnter();
	for (auto child : _children)
	{
		child->setOpacity(0.0f);
		child->runAction(FadeIn::create(0.5f));
	}
}

void MenuLayer::exitSchedule(float deltaTime)
{
	this->removeFromParentAndCleanup(true);
}

void MenuLayer::update(float deltaTime)
{
}