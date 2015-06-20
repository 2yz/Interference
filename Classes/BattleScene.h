#ifndef BattleScene_H_
#define BattleScene_H_

#include "cocos2d.h"
#include "HUDLayer.h"
#include "BattleLayer.h"

class BattleScene : public cocos2d::Scene
{
public:
	BattleScene();
	virtual ~BattleScene();
	virtual bool init() override;
	CREATE_FUNC(BattleScene);
	// static BattleScene* getInstance();
	HUDLayer* getHUDLayer();
	// CameraNode* getCameraLayer();

	// BulletLayer* getBulletLayer();
	// PlayerLayer* getPlayerLayer();
	// EnemyBulletLayer* getEnemyBulletLayer();
	// EnemyLayer* getEnemyLayer();
protected:
	// static GameBackgroundLayer* gameBackgroundLayer;
	static BattleScene* battleScene;
	BattleLayer* battleLayer;
	HUDLayer* _HUDLayer;
	// static CameraNode* cameraNode;
	// cocos2d::Camera* camera_;
	virtual void update(float deltaTime) override;
	// static BulletLayer* bulletLayer;
	// static PlayerLayer* playerLayer;
	// static EnemyBulletLayer* enemyBulletLayer;
	// static EnemyLayer* enemyLayer;
};

#endif /* BattleScene_H_ */