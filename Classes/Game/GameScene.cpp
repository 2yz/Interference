#include "GameScene.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

// Scene* GameScene::gameScene = nullptr;
// GameBackgroundLayer* GameScene::gameBackgroundLayer = nullptr;
// PlayerLayer* GameScene::playerLayer = nullptr;
// BulletLayer* GameScene::bulletLayer = nullptr;
// UILayer* GameScene::uiLayer = nullptr;

// Scene* GameScene::create()
// {
// gameScene = Scene::create();



// auto mySprite = Sprite::create("img_bg_1.jpg");
// mySprite->setAnchorPoint(Vec2::ZERO);
// mySprite->setScale(3);
// gameScene->addChild(mySprite);


// return gameScene;
// }
/*
bool GameScene::init()
{
gameBackgroundLayer = GameBackgroundLayer::create();
gameBackgroundLayer->setParent(this);
gameBackgroundLayer->setName("GameBackgroundLayer");
playerLayer = PlayerLayer::create();
playerLayer->setParent(this);
bulletLayer = BulletLayer::create();
bulletLayer->setParent(this);
uiLayer = UILayer::create();
uiLayer->setParent(this);


this->addChild(gameBackgroundLayer, 1);
this->addChild(playerLayer, 2);
this->addChild(uiLayer, 3);

// auto rootNode = CSLoader::createNode("MainScene.csb");
// gameScene->addChild(rootNode);

auto lable = Label::createWithTTF("Label", "fonts/Marker Felt.ttf", 32);
lable->setPosition(200, 200);
this->addChild(lable, 2);

return true;
}
*/

/*
PlayerLayer* GameScene::getPlayerLayer()
{
return this->playerLayer;
}
*/

GameBackgroundLayer* GameScene::gameBackgroundLayer = nullptr;
UILayer* GameScene::uiLayer = nullptr;
BulletLayer* GameScene::bulletLayer = nullptr;
PlayerLayer* GameScene::playerLayer = nullptr;
EnemyBulletLayer* GameScene::enemyBulletLayer = nullptr;
EnemyLayer* GameScene::enemyLayer = nullptr;

GameScene::GameScene()
{	
}

GameScene::~GameScene()
{
	gameBackgroundLayer = nullptr;
	playerLayer = nullptr;
	bulletLayer = nullptr;
	uiLayer = nullptr;
}

bool GameScene::init()
{
	gameBackgroundLayer = GameBackgroundLayer::create();
	gameBackgroundLayer->setParent(this);
	playerLayer = PlayerLayer::create();
	playerLayer->setParent(this);
	bulletLayer = BulletLayer::create();
	bulletLayer->setParent(this);
	uiLayer = UILayer::create();
	uiLayer->setParent(this);
	// enemyBulletLayer = EnemyBulletLayer::create();
	// enemyBulletLayer->setParent(this);
	enemyLayer = EnemyLayer::create();
	enemyLayer->setParent(this);

	this->addChild(gameBackgroundLayer, 1);
	this->addChild(uiLayer, 4);
	this->addChild(bulletLayer, 3);
	this->addChild(playerLayer, 2);
	// this->addChild(enemyBulletLayer, 3);
	this->addChild(enemyLayer, 2);

	auto lable = Label::createWithTTF("Label", "fonts/Marker Felt.ttf", 32);
	lable->setPosition(200, 200);
	this->addChild(lable, 2);
	
	// TODO ÐÞ¸ÄListenerÎ»ÖÃ
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(GameScene::mouseDown, this);
	listener->onMouseMove = CC_CALLBACK_1(GameScene::mouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

EnemyBulletLayer* GameScene::getEnemyBulletLayer()
{
	return this->enemyBulletLayer;
}

EnemyLayer* GameScene::getEnemyLayer()
{
	return this->enemyLayer;
}

UILayer* GameScene::getUILayer()
{
	return this->uiLayer;
}

BulletLayer* GameScene::getBulletLayer()
{
	return this->bulletLayer;
}

PlayerLayer* GameScene::getPlayerLayer()
{
	return this->playerLayer;
}

void GameScene::mouseDown(cocos2d::Event* event)
{
	auto e = static_cast<EventMouse*>(event);
	log("#DOWN# X: %f ; Y: %f", e->getCursorX(), e->getCursorY());
	auto x = e->getCursorX();
	auto y = e->getCursorY();
}

void GameScene::mouseMove(cocos2d::Event* event)
{
	auto e = static_cast<EventMouse*>(event);
	log("#MOVE# X: %f ; Y: %f", e->getCursorX(), e->getCursorY());
	auto x = e->getCursorX();
	auto y = e->getCursorY();
}