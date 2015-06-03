#include "CameraNode.h"
#include "BattleLayer.h"

USING_NS_CC;

CameraNode::CameraNode() : battleLayer(nullptr), gameBackgroundLayer(nullptr)
{
}

CameraNode::~CameraNode()
{
	gameBackgroundLayer = nullptr;
	battleLayer = nullptr;
}

bool CameraNode::init()
{
	if (!BaseCamera::init())
	{
		return false;
	}

	gameBackgroundLayer = GameBackgroundLayer::create();
	gameBackgroundLayer->setParent(this);
	battleLayer = BattleLayer::create();
	battleLayer->setParent(this);
	
	this->setTraceNode(battleLayer->getPlayerPlane());	
	this->addChild(gameBackgroundLayer);
	this->addChild(battleLayer);

	return true;
}

GameBackgroundLayer* CameraNode::getGameBackgroundLayer()
{
	return this->gameBackgroundLayer;
}

BattleLayer* CameraNode::getBattleLayer()
{
	return this->battleLayer;
}
