#ifndef PLAYERPLANE_H_
#define PLAYERPLANE_H_

#include "BasePlayer.h"

class PlayerPlane : public BasePlayer
{
public:
	PlayerPlane();
	// virtual bool init() override;
	// static PlayerPlane* create();
	CREATE_FUNC(PlayerPlane);
};

#endif /* PLAYERPLANE_H_ */