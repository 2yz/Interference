#ifndef BASEPLAYER_H_
#define BASEPLAYER_H_

#include "cocos2d.h"
#include "BaseTraced.h"
#include "BasePlane.h"

class BasePlayer : public BasePlane, public BaseTraced
{
public:
	BasePlayer();
	virtual bool init() override;
protected:
	const int initHP;
	const float acceleration;
	const float maxSpeed;
	virtual void update(float deltaTime) override;
};

#endif /* BASEPLAYER_H_ */