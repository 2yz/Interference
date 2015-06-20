#ifndef GAMEBACKGROUNDLAYER_H_
#define GAMEBACKGROUNDLAYER_H_

#include "cocos2d.h"

class GameBackgroundLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameBackgroundLayer);
	virtual bool init() override;
protected:
	cocos2d::Sprite* background_;
};

#endif /* GAMEBACKGROUNDLAYER_H_ */