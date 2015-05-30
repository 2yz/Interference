#ifndef BASEPLANE_H_
#define BASEPLANE_H_

#include "BaseObject.h"

class BasePlane : public BaseObject
{
public:
	BasePlane();
	explicit BasePlane(float radius);
	static BasePlane* create();
	virtual void onEnter() override;
protected:
	cocos2d::Sprite* plane;

};

#endif /* BASEPLANE_H_ */