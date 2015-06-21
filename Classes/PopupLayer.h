#ifndef POPUPLAYER_H_
#define POPUPLAYER_H_

#include "cocos2d.h"
#include <ui/UIButton.h>

#define CALL_INIT() \
if (pRet && pRet->init()) \
{ \
	pRet->autorelease(); \
	return pRet; \
} \
else \
{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
} 

class PopupLayer : public cocos2d::LayerColor
{
public:
	PopupLayer(const std::string& label_text, const std::string& button_text);
	virtual bool init() override;
	virtual void onEnter() override;
	void onDestroy();
	void exitSchedule(float delta_time);
	virtual void buttonListener(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
protected:
	std::string label_text_;
	std::string button_text_;
	cocos2d::Label* label_;
	cocos2d::ui::Button* button_;
};

#endif /* POPUPLAYER_H_ */
