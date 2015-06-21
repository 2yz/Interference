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
	int getScore();
	void updateScore();
	virtual void update(float delta_time) override;
private:
	int score_;
	cocos2d::Label* score_label_;
	cocos2d::Label* score_num_label_;
	cocos2d::ProgressTimer* blood_bar_;
	cocos2d::Sprite* blood_bar_box_;
	cocos2d::ProgressTimer* attack_sprite_;
	cocos2d::Sprite* attack_dark_sprite_;
};

#endif /* UILAYER_H_ */
