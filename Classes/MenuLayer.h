#ifndef MENULAYER_H_
#define MENULAYER_H_

#include "cocos2d.h"
#include <ui/UIButton.h>

class MenuLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(MenuLayer);
	MenuLayer();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	void onDestroy();
	void exitSchedule(float deltaTime);
	virtual void update(float deltaTime) override;
protected:
	bool isHelp_;
	cocos2d::Sprite* logo_;
	cocos2d::Sprite* help_instruction_;
	cocos2d::Sprite* background_;
	cocos2d::ui::Button* start_button_;
	cocos2d::ui::Button* help_button_;
	cocos2d::ui::Button* exit_button_;
	int background_music;
};

#endif /* MENULAYER_H_ */
