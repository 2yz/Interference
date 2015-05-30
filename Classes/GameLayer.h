#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "cocos2d.h"
#include "PlayerPlane.h"

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	virtual bool init() override;
	CREATE_FUNC(GameLayer);
	virtual void update(float delta) override;
	PlayerPlane* getPlayerPlane();
protected:
	PlayerPlane* playerPlane;
};

#endif /* GAMELAYER_H_ */