#include "CameraNode.h"
#include "BattleLayer.h"

USING_NS_CC;

// GameBackgroundLayer* CameraNode::gameBackgroundLayer = nullptr;
// BattleLayer* CameraNode::battleLayer = nullptr;
// BulletLayer* CameraNode::bulletLayer = nullptr;
// PlayerLayer* CameraNode::playerLayer = nullptr;
// EnemyBulletLayer* CameraNode::enemyBulletLayer = nullptr;
// EnemyLayer* CameraNode::enemyLayer = nullptr;


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

// BulletLayer* CameraNode::getBulletLayer()
// {
// 	return this->bulletLayer;
// }
// 
// PlayerLayer* CameraNode::getPlayerLayer()
// {
// 	return this->playerLayer;
// }
// 
// EnemyBulletLayer* CameraNode::getEnemyBulletLayer()
// {
// 	return this->enemyBulletLayer;
// }
// 
// EnemyLayer* CameraNode::getEnemyLayer()
// {
// 	return this->enemyLayer;
// }

BattleLayer* CameraNode::getBattleLayer()
{
	return this->battleLayer;
}

// void CameraNode::update(float deltaTime)
// {	
// 	
// }