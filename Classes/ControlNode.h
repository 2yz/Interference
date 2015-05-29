#ifndef CAMERALAYER_H_
#define CAMERALAYER_H_

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
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void update(float delta) override;
};

#endif /* CAMERALAYER_H_ */