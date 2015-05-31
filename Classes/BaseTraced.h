#ifndef BASETRACED_H_
#define BASETRACED_H_

#include "cocos2d.h"

class BaseTraced
{
public:
	BaseTraced();
	float getTraceCoefficient();
	void setTraceCoefficient(float maxSpeed, float acceleration,float deltaTime);
protected:
	float traceCoefficient;
};

#endif /* BASETRACED_H_ */