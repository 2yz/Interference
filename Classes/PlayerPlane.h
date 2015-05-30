#ifndef PLAYERPLANE_H_
#define PLAYERPLANE_H_

#include "BasePlane.h"

class PlayerPlane : public BasePlane
{
public:
	PlayerPlane();
	virtual bool init() override;
	static PlayerPlane* create();
	virtual void update(float delta) override;
protected:
	const int initHP;
	const float acceleration;
	const float maxSpeed;
};

#endif /* PLAYERPLANE_H_ */