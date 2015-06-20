#ifndef LOGOSCENE_H_
#define LOGOSCENE_H_

#include "cocos2d.h"

class LogoScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(LogoScene);
	LogoScene();
	virtual bool init() override;
	virtual void onEnter() override;
	void spriteFrameCallBack(cocos2d::Texture2D *texture);
	void loadingCallBack(cocos2d::Texture2D *texture);
	void startBattle();
protected:
	bool animation_finish_;
	bool load_finish_;
	int loaded_num_;
	int total_num_;
};

#endif /* LOGOSCENE_H_ */