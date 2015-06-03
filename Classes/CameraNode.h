#ifndef CAMERANODE_H_
#define CAMERANODE_H_

#include "BaseCamera.h"
#include "GameBackgroundLayer.h"
#include "BulletLayer.h"
#include "PlayerLayer.h"
#include "EnemyBulletLayer.h"
#include "EnemyLayer.h"
#include "BattleLayer.h"

class CameraNode : public BaseCamera
{
public:
	CameraNode();
	virtual ~CameraNode();
	virtual bool init() override;
	CREATE_FUNC(CameraNode);
	float time;
	GameBackgroundLayer* getGameBackgroundLayer();
	// BulletLayer* getBulletLayer();
	// PlayerLayer* getPlayerLayer();
	// EnemyBulletLayer* getEnemyBulletLayer();
	// EnemyLayer* getEnemyLayer();
	BattleLayer* getBattleLayer();
protected:
	BattleLayer* battleLayer;
	GameBackgroundLayer* gameBackgroundLayer;
	// static BulletLayer* bulletLayer;
	// static PlayerLayer* playerLayer;
	// static EnemyBulletLayer* enemyBulletLayer;
	// static EnemyLayer* enemyLayer;
	// virtual void update(float deltaTime) override;
};

#endif /* CAMERANODE_H_ */