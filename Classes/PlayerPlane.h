#ifndef PLAYERPLANE_H_
#define PLAYERPLANE_H_

#include "BasePlane.h"

class PlayerPlane : public BasePlane
{
public:
	PlayerPlane();
	static PlayerPlane* create();
protected:
	cocos2d::Sprite* plane;

};

#endif /* PLAYERPLANE_H_ */