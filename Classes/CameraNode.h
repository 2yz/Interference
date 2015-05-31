#ifndef CAMERANODE_H_
#define CAMERANODE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "BulletLayer.h"
#include "PlayerLayer.h"
#include "EnemyBulletLayer.h"
#include "EnemyLayer.h"
#include "GameLayer.h"

class CameraNode : public cocos2d::Node{
public:
	CameraNode();
	virtual ~CameraNode();
	virtual bool init() override;
	CREATE_FUNC(CameraNode);
	float time;
	GameBackgroundLayer* getGameBackgroundLayer();
	BulletLayer* getBulletLayer();
	PlayerLayer* getPlayerLayer();
	EnemyBulletLayer* getEnemyBulletLayer();
	EnemyLayer* getEnemyLayer();
private:
	static GameBackgroundLayer* gameBackgroundLayer;
	static GameLayer* gameLayer;
	static BulletLayer* bulletLayer;
	static PlayerLayer* playerLayer;
	static EnemyBulletLayer* enemyBulletLayer;
	static EnemyLayer* enemyLayer;
	virtual void update(float deltaTime) override;
};

#endif /* CAMERANODE_H_ */