#include "BaseCamera.h"
#include "ConfigUtil.h"
#include "BaseTraced.h"
#include "Controller.h"

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
	scaleCoefficient = 1.0f;
	this->setScale(scaleCoefficient);
	this->scheduleUpdate();
	return true;
}

void BaseCamera::setTraceNode(BasePlayer* traceNode)
{
	this->traceNode = traceNode;
}

void BaseCamera::update(float deltaTime)
{
	// auto cameraPosition = Director::getInstance()->getRunningScene()->getDefaultCamera()->getPosition();
	// log("CAMERA X: %f Y: %f", cameraPosition.x, cameraPosition.y);
	if (traceNode != nullptr)
	{
		auto positionDelta = this->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) + traceNode->getPosition()*scaleCoefficient;
		// log("P Delta X: %f Y: %f", positionDelta.x, positionDelta.y);
		this->setPosition(this->getPosition() - positionDelta * traceNode->getTraceCoefficient() * deltaTime);
		// Use Default Camera
		// auto positionDelta = traceNode->getPosition() + Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) - Director::getInstance()->getRunningScene()->getDefaultCamera()->getPosition();
		// Director::getInstance()->getRunningScene()->getDefaultCamera()->setPosition(Director::getInstance()->getRunningScene()->getDefaultCamera()->getPosition() + positionDelta * traceNode->getTraceCoefficient() * deltaTime);
	}
	// if (Controller::getKeyE() == true)
	// {
	// 	this->setScale(random(0.5f, 1.5f));
	// 	randomScale = true;
	// }
	// else if (randomScale == true)
	// {
	// 	scaleCoefficient = 1.0f;
	// 	this->setScale(scaleCoefficient);
	// 	randomScale = false;
	// }
}