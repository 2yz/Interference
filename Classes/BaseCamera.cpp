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
	// scaleCoefficient = 1.0f;
	// this->setScale(scaleCoefficient);
	this->scheduleUpdate();
	return true;
}

void BaseCamera::setTraceNode(BasePlayer* traceNode)
{
	this->traceNode = traceNode;
}

void BaseCamera::update(float deltaTime)
{
	auto cameraPosition = Director::getInstance()->getRunningScene()->getDefaultCamera()->getPosition3D();
	// log("CAMERA X: %f Y: %f Z:%f", cameraPosition.x, cameraPosition.y,cameraPosition.z);
	if (traceNode != nullptr)
	{
		auto positionDelta = this->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) + traceNode->getPosition();
		// auto positionDelta = this->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) + traceNode->getPosition()*scaleCoefficient;
		// log("P Delta X: %f Y: %f", positionDelta.x, positionDelta.y);
		this->setPosition(this->getPosition() - positionDelta * traceNode->getTraceCoefficient() * deltaTime);

		// Use Default Camera
		// auto positionDelta = traceNode->getPosition() + Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) - Director::getInstance()->getRunningScene()->getDefaultCamera()->getPosition();
		// auto eye = Vec3(Director::getInstance()->getRunningScene()->getDefaultCamera()->getPosition3D() + Vec3(positionDelta.x * traceNode->getTraceCoefficient() * deltaTime, positionDelta.y * traceNode->getTraceCoefficient() * deltaTime, 0.0f));
		// Director::getInstance()->getRunningScene()->getDefaultCamera()->setPosition3D(eye);
		// Director::getInstance()->getRunningScene()->getDefaultCamera()->lookAt(eye);		
		// Director::getInstance()->getRunningScene()->getDefaultCamera()->setPosition3D(Vec3(eyeX,eyeY,0.0f));
		// Director::getInstance()->getRunningScene()->getDefaultCamera()->lookAt(Vec3(eyeX, eyeY, 0.0f));
	}
}