#include "MenuLayer.h"
#include "ConfigUtil.h"
#include "BattleScene.h"
#include <AudioEngine.h>

USING_NS_CC;

MenuLayer::MenuLayer() : isHelp_(false)
{
}

bool MenuLayer::init()
{
	if (!Layer::init())
		return false;
	background_ = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(MENU_BACKGROUND_TEXTURE));
	background_->setPosition(config::visible_size / 2);
	this->addChild(background_);
	logo_ = Sprite::createWithSpriteFrameName(LOGO_SPRITE_FRAME);
	logo_->setPosition(config::visible_width - 380.0f, config::visible_height / 2);
	this->addChild(logo_);
	help_instruction_ = Sprite::createWithSpriteFrameName(HELP_SPRITE_FRAME);
	help_instruction_->setPosition(config::visible_width - 380.0f, config::visible_height / 2);
	this->addChild(help_instruction_);
	start_button_ = ui::Button::create(BUTTON_NORMAL_TEXTURE, BUTTON_PRESS_TEXTURE, BUTTON_NORMAL_TEXTURE);
	start_button_->setTitleText("START");
	start_button_->setTitleFontName(HELVETICA_NEUE_FONT);
	start_button_->setTitleFontSize(28.0f);
	start_button_->setPosition(Vec2(240.0f, config::visible_height / 2 + 90.0f));
	start_button_->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			BattleScene::getInstance()->startBattle();
			onDestroy();
			break;
		default:
			break;
		}
	});
	this->addChild(start_button_);
	help_button_ = ui::Button::create(BUTTON_NORMAL_TEXTURE, BUTTON_PRESS_TEXTURE, BUTTON_NORMAL_TEXTURE);
	help_button_->setTitleText("HELP");
	help_button_->setTitleFontName(HELVETICA_NEUE_FONT);
	help_button_->setTitleFontSize(28.0f);
	help_button_->setPosition(Vec2(240.0f, config::visible_height / 2));
	help_button_->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (!isHelp_)
			{
				help_instruction_->runAction(FadeIn::create(0.6f));
				logo_->runAction(FadeOut::create(0.6f));
				isHelp_ = true;
			}
			else
			{
				logo_->runAction(FadeIn::create(0.6f));
				help_instruction_->runAction(FadeOut::create(0.6f));
				isHelp_ = false;
			}
			break;
		default:
			break;
		}
	});
	this->addChild(help_button_);
	exit_button_ = ui::Button::create(BUTTON_NORMAL_TEXTURE, BUTTON_PRESS_TEXTURE, BUTTON_NORMAL_TEXTURE);
	exit_button_->setTitleText("EXIT");
	exit_button_->setTitleFontName(HELVETICA_NEUE_FONT);
	exit_button_->setTitleFontSize(28.0f);
	exit_button_->setPosition(Vec2(240.0f, config::visible_height / 2 - 90.0f));
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
		child->setOpacity(0.0f);
	background_->runAction(FadeIn::create(0.5f));
	logo_->runAction(FadeIn::create(0.5f));
	start_button_->runAction(FadeIn::create(0.5f));
	help_button_->runAction(FadeIn::create(0.5f));
	exit_button_->runAction(FadeIn::create(0.5f));
	background_music_ = experimental::AudioEngine::play2d(MENU_MUSIC, true, MENU_MUSIC_VOLUME);
}

void MenuLayer::onExit()
{
	experimental::AudioEngine::stop(background_music_);
	Layer::onExit();
}

void MenuLayer::onDestroy()
{
	for (auto child : _children)
		child->runAction(FadeOut::create(0.5f));
	scheduleOnce(schedule_selector(MenuLayer::exitSchedule), 0.6f);
}

void MenuLayer::exitSchedule(float delta_time)
{
	this->removeFromParentAndCleanup(true);
}

void MenuLayer::update(float delta_time)
{
}