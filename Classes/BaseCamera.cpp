#include "BaseCamera.h"
#include "ConfigUtil.h"
#include "BaseTraced.h"

USING_NS_CC;

BaseCamera::BaseCamera() : traceNode(nullptr)
{
}

bool BaseCamera::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

void BaseCamera::setTraceNode(BasePlayer* traceNode)
{
	this->traceNode = traceNode;
}

void BaseCamera::update(float deltaTime)
{
	if (traceNode != nullptr)
	{
		auto positionDelta = this->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) + traceNode->getPosition();
		// log("P Delta X: %f Y: %f", positionDelta.x, positionDelta.y);
		this->setPosition(this->getPosition() - positionDelta * traceNode->getTraceCoefficient() * deltaTime);
	}
}