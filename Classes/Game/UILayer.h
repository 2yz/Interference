#ifndef UILAYER_H_
#define UILAYER_H_

#include "cocos2d.h"

class UILayer : public cocos2d::Layer
{
public:
	UILayer();
	virtual bool init() override;
	CREATE_FUNC(UILayer);
	void addScoreBy(int addScore);
	void updateHPIndicator();
	void setLaunchButtonEnable();
	int getScore();
private:
	int score;
	cocos2d::Label* scoreLabel;
	cocos2d::MenuItemSprite* pauseButtonItem;
	cocos2d::MenuItemSprite* launchButtonItem;
	cocos2d::ProgressTimer* HPIndicator;
	cocos2d::Menu* pauseButton;
	cocos2d::Menu* launchButton;

	void updateScore();
	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuLaunchCallback(cocos2d::Ref* pSender);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event) override;
};

#endif /* UILAYER_H_ */
