#ifndef BASEPLANE_H_
#define BASEPLANE_H_

#include "BaseObject.h"

class BasePlane : public BaseObject
{
public:
	BasePlane();
	explicit BasePlane(float radius);
	virtual bool init() override;
	virtual void onEnter() override;
	// static BasePlane* create();
protected:
	cocos2d::Sprite* normalShapeUp;
	cocos2d::Sprite* normalShapeDown;
	cocos2d::Sprite* smallShapeUp;
	cocos2d::Sprite* smallShapeDown;
    cocos2d::ParticleSystemQuad* TailFire;

};

#endif /* BASEPLANE_H_ */