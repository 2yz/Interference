#ifndef MOUSELAYER_H_
#define MOUSELAYER_H_

#include "cocos2d.h"

class MouseLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(MouseLayer);
	MouseLayer();
	virtual bool init() override;

protected:
	cocos2d::Sprite* mouse_sprite_;
	virtual void update(float delta_time) override;
};

#endif /* MOUSELAYER_H_ */