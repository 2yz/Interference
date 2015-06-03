#ifndef PLAYERPLANE_H_
#define PLAYERPLANE_H_

#include "BasePlayer.h"

class PlayerPlane : public BasePlayer
{
public:
	PlayerPlane();
	// virtual bool init() override;
	// static PlayerPlane* create(float x,float y);
	CREATE_FUNC(PlayerPlane);

	virtual void onEnter() override;
};

#endif /* PLAYERPLANE_H_ */