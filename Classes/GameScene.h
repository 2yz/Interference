#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "UILayer.h"
#include "ControlNode.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene();
	virtual ~GameScene();
	virtual bool init() override;
	CREATE_FUNC(GameScene);
	UILayer* getUILayer();
	ControlNode* getCameraLayer();
	// BulletLayer* getBulletLayer();
	// PlayerLayer* getPlayerLayer();
	// EnemyBulletLayer* getEnemyBulletLayer();
	// EnemyLayer* getEnemyLayer();
	void mouseDown(cocos2d::Event* event);
	void mouseMove(cocos2d::Event* event);
private:
	// static GameBackgroundLayer* gameBackgroundLayer;
	static UILayer* uiLayer;
	static ControlNode* controlNode;
	// static BulletLayer* bulletLayer;
	// static PlayerLayer* playerLayer;
	// static EnemyBulletLayer* enemyBulletLayer;
	// static EnemyLayer* enemyLayer;
};


#endif /* GAMESCENE_H_ */