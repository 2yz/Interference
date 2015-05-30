#ifndef BASEPLANE_H_
#define BASEPLANE_H_

#include "BaseObject.h"

class BasePlane : public BaseObject
{
public:
	BasePlane();
	explicit BasePlane(float radius);
	virtual bool init() override;
	static BasePlane* create();
protected:
	cocos2d::Sprite* plane;

};

#endif /* BASEPLANE_H_ */