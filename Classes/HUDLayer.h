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
	virtual void update(float deltaTime) override;
private:
	int score_;
	cocos2d::Label* score_label_;
	cocos2d::Label* score_num_label_;
	cocos2d::ProgressTimer* blood_bar_;
	cocos2d::Sprite* blood_bar_box_;
	cocos2d::ProgressTimer* attack_sprite_;
	cocos2d::Sprite* attack_dark_sprite_;
	cocos2d::MenuItemSprite* pauseButtonItem;
	cocos2d::MenuItemSprite* launchButtonItem;
	cocos2d::ProgressTimer* HPIndicator;
	cocos2d::Menu* pauseButton;
	cocos2d::Menu* launchButton;	
};

#endif /* UILAYER_H_ */
