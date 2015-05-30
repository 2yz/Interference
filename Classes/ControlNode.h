#ifndef CONTROLNODE_H_
#define CONTROLNODE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "BulletLayer.h"
#include "PlayerLayer.h"
#include "EnemyBulletLayer.h"
#include "EnemyLayer.h"

class ControlNode : public cocos2d::Node{
public:
	ControlNode();
	virtual ~ControlNode();
	virtual bool init() override;
	CREATE_FUNC(ControlNode);
	float time;
	GameBackgroundLayer* getGameBackgroundLayer();
	BulletLayer* getBulletLayer();
	PlayerLayer* getPlayerLayer();
	EnemyBulletLayer* getEnemyBulletLayer();
	EnemyLayer* getEnemyLayer();
private:
	static GameBackgroundLayer* gameBackgroundLayer;
	static BulletLayer* bulletLayer;
	static PlayerLayer* playerLayer;
	static EnemyBulletLayer* enemyBulletLayer;
	static EnemyLayer* enemyLayer;
	virtual void update(float delta) override;
};

#endif /* CONTROLNODE_H_ */