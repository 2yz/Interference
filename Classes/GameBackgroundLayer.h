#ifndef GAMEBACKGROUNDLAYER_H_
#define GAMEBACKGROUNDLAYER_H_

#include "cocos2d.h"

class GameBackgroundLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameBackgroundLayer);
	virtual bool init() override;
	virtual void onEnter() override;
};

#endif /* GAMEBACKGROUNDLAYER_H_ */