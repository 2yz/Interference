#ifndef PAUSELAYER_H_
#define PAUSELAYER_H_

#include "PopupLayer.h"

class PauseLayer : public PopupLayer
{
public:
	static PauseLayer* create(const std::string& label_text, const std::string& button_text);
	PauseLayer(const std::string& label_text, const std::string& button_text);
	virtual bool init() override;
	virtual void buttonListener(Ref* sender, cocos2d::ui::Widget::TouchEventType type) override;
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
};

#endif /* PAUSELAYER_H_ */
