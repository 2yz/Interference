#include "PopupLayer.h"
#include "ConfigUtil.h"

USING_NS_CC;

PopupLayer::PopupLayer(const std::string& label_text, const std::string& button_text) : label_text_(label_text), button_text_(button_text)
{
}

bool PopupLayer::init()
{
	if (!LayerColor::init())
		return false;
	setColor(Color3B(0, 0, 0));
	setOpacity(128);
	label_ = Label::createWithTTF(label_text_, HELVETICA_NEUE_FONT, 42.0f);
	label_->setPosition(config::visible_size / 2 + Size(0.0f, 46.0f));
	this->addChild(label_);
	button_ = ui::Button::create(BUTTON_NORMAL_TEXTURE, BUTTON_PRESS_TEXTURE, BUTTON_NORMAL_TEXTURE);
	button_->addTouchEventListener(CC_CALLBACK_2(PopupLayer::buttonListener, this));
	button_->setTitleText(button_text_);
	button_->setTitleFontName(HELVETICA_NEUE_FONT);
	button_->setTitleFontSize(28.0f);
	button_->setPosition(config::visible_size / 2 - Size(0.0f, 36.0f));
	this->addChild(button_);
	return true;
}

void PopupLayer::onEnter()
{
	LayerColor::onEnter();
	for (auto child : _children)
	{
		child->setOpacity(0.0f);
		child->runAction(FadeIn::create(0.5f));
	}
}

void PopupLayer::onDestroy()
{
	for (auto child : _children)
		child->runAction(FadeOut::create(0.5f));
	scheduleOnce(schedule_selector(PopupLayer::exitSchedule), 0.5f);
}

void PopupLayer::exitSchedule(float delta_time)
{
	this->removeFromParentAndCleanup(true);
}

void PopupLayer::buttonListener(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
}