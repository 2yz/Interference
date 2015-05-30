#include "GameLayer.h"
#include "ConfigUtil.h"

USING_NS_CC;

GameLayer::GameLayer()
{
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// »æÖÆPlayer
	playerPlane = PlayerPlane::create();
	playerPlane->setPosition(0, 0);
	
	this->addChild(playerPlane);
	this->scheduleUpdate();

	return true;
}

void GameLayer::update(float delta)
{
	log("GameLayer::update(float delta)");
}

PlayerPlane* GameLayer::getPlayerPlane()
{
	return playerPlane;
}