#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "PlayerLayer.h"
#include "BulletLayer.h"
#include "UILayer.h"
#include "EnemyBulletLayer.h"
#include "EnemyLayer.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene();
	virtual ~GameScene();
	virtual bool init() override;
	CREATE_FUNC(GameScene);
	UILayer* getUILayer();
	BulletLayer* getBulletLayer();
	PlayerLayer* getPlayerLayer();
	EnemyBulletLayer* getEnemyBulletLayer();
	EnemyLayer* getEnemyLayer();
	void mouseDown(cocos2d::Event* event);
	void mouseMove(cocos2d::Event* event);
private:
	static GameBackgroundLayer* gameBackgroundLayer;
	static UILayer* uiLayer;
	static BulletLayer* bulletLayer;
	static PlayerLayer* playerLayer;
	static EnemyBulletLayer* enemyBulletLayer;
	static EnemyLayer* enemyLayer;
};

/*
class GameScene
{
public:
	static cocos2d::Scene* create();
};
*/

#endif /* GAMESCENE_H_ */