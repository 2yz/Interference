#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "UILayer.h"
#include "CameraNode.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene();
	virtual ~GameScene();
	virtual bool init() override;
	CREATE_FUNC(GameScene);
	UILayer* getUILayer();
	CameraNode* getCameraLayer();
	// BulletLayer* getBulletLayer();
	// PlayerLayer* getPlayerLayer();
	// EnemyBulletLayer* getEnemyBulletLayer();
	// EnemyLayer* getEnemyLayer();
private:
	// static GameBackgroundLayer* gameBackgroundLayer;
	static UILayer* uiLayer;
	static CameraNode* CameraNode;
	// static BulletLayer* bulletLayer;
	// static PlayerLayer* playerLayer;
	// static EnemyBulletLayer* enemyBulletLayer;
	// static EnemyLayer* enemyLayer;
};


#endif /* GAMESCENE_H_ */