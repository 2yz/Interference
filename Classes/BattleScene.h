#ifndef BattleScene_H_
#define BattleScene_H_

#include "cocos2d.h"
#include "UILayer.h"
#include "CameraNode.h"

class BattleScene : public cocos2d::Scene
{
public:
	BattleScene();
	virtual ~BattleScene();
	virtual bool init() override;
	CREATE_FUNC(BattleScene);
	static BattleScene* getInstance();
	UILayer* getUILayer();
	CameraNode* getCameraLayer();

	// BulletLayer* getBulletLayer();
	// PlayerLayer* getPlayerLayer();
	// EnemyBulletLayer* getEnemyBulletLayer();
	// EnemyLayer* getEnemyLayer();
private:
	// static GameBackgroundLayer* gameBackgroundLayer;
	static BattleScene* battleScene;
	static UILayer* uiLayer;
	static CameraNode* cameraNode;
	// static BulletLayer* bulletLayer;
	// static PlayerLayer* playerLayer;
	// static EnemyBulletLayer* enemyBulletLayer;
	// static EnemyLayer* enemyLayer;
};

#endif /* BattleScene_H_ */