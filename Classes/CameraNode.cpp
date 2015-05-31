#include "CameraNode.h"
#include "GameLayer.h"

USING_NS_CC;

GameBackgroundLayer* CameraNode::gameBackgroundLayer = nullptr;
GameLayer* CameraNode::gameLayer = nullptr;
BulletLayer* CameraNode::bulletLayer = nullptr;
PlayerLayer* CameraNode::playerLayer = nullptr;
EnemyBulletLayer* CameraNode::enemyBulletLayer = nullptr;
EnemyLayer* CameraNode::enemyLayer = nullptr;


CameraNode::CameraNode()
{
}

CameraNode::~CameraNode()
{
	gameBackgroundLayer = nullptr;
	bulletLayer = nullptr;
	playerLayer = nullptr;
	enemyBulletLayer = nullptr;
	enemyLayer = nullptr;
}

bool CameraNode::init()
{
	if (!BaseCamera::init())
	{
		return false;
	}
	gameBackgroundLayer = GameBackgroundLayer::create();
	gameBackgroundLayer->setParent(this);
	auto gameLayer = GameLayer::create();
	gameLayer->setParent(this);
	this->setTraceNode(gameLayer->getPlayerPlane());
	this->addChild(gameBackgroundLayer);
	this->addChild(gameLayer);

	this->scheduleUpdate();

	return true;
}

GameBackgroundLayer* CameraNode::getGameBackgroundLayer()
{
	return this->gameBackgroundLayer;
}

BulletLayer* CameraNode::getBulletLayer()
{
	return this->bulletLayer;
}

PlayerLayer* CameraNode::getPlayerLayer()
{
	return this->playerLayer;
}

EnemyBulletLayer* CameraNode::getEnemyBulletLayer()
{
	return this->enemyBulletLayer;
}

EnemyLayer* CameraNode::getEnemyLayer()
{
	return this->enemyLayer;
}

// void CameraNode::update(float deltaTime)
// {	
// 	
// }