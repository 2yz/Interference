#ifndef UILAYER_H_
#define UILAYER_H_

#include "cocos2d.h"

class HUDLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(HUDLayer);
	HUDLayer();
	virtual bool init() override;
	void setEventListener();
	void addScoreBy(int addScore);
	void updateHPIndicator();
	void setLaunchButtonEnable();
	int getScore();
	void updateScore();
	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuLaunchCallback(cocos2d::Ref* pSender);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event) override;
	virtual void update(float deltaTime) override;
private:
	int score;
	cocos2d::Label* scoreLabel;
	cocos2d::MenuItemSprite* pauseButtonItem;
	cocos2d::MenuItemSprite* launchButtonItem;
	cocos2d::ProgressTimer* HPIndicator;
	cocos2d::Menu* pauseButton;
	cocos2d::Menu* launchButton;	
};

#endif /* UILAYER_H_ */
