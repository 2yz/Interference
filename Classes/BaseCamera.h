#ifndef BASECAMERA_H_
#define BASECAMERA_H_

#include "cocos2d.h"
#include "BasePlayer.h"

class BaseCamera : public cocos2d::Node
{
public:
	BaseCamera();
	virtual bool init() override;
	void setTraceNode(BasePlayer* traceNode);
protected:
	BasePlayer* traceNode;
	float scaleCoefficient;
	virtual void update(float deltaTime) override;
};

#endif /* BASECAMERA_H_ */