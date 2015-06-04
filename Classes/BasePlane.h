#ifndef BASEPLANE_H_
#define BASEPLANE_H_

#include "BaseObject.h"

class BasePlane : public BaseObject
{
public:
	explicit BasePlane(float radius = 60.0f);
	virtual bool init() override;
	virtual void onEnter() override;
	// static BasePlane* create();
protected:
	// cocos2d::Sprite* normalShapeUp;
	// cocos2d::Sprite* normalShapeDown;
	// cocos2d::Sprite* smallShapeUp;
	// cocos2d::Sprite* smallShapeDown;
	cocos2d::Vector<cocos2d::Sprite*> extraSpriteVector;
	float linearDamping;
	float shapeRadius;
	float rotateVelocity; // degree per second
	virtual void update(float deltaTime) override;
};

#endif /* BASEPLANE_H_ */