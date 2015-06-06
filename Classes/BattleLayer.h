#ifndef BattleLayer_H_
#define BattleLayer_H_

#include "cocos2d.h"
#include "Player.h"

class BattleLayer : public cocos2d::Layer
{
public:
	BattleLayer();
	virtual ~BattleLayer();
	virtual bool init() override;
	CREATE_FUNC(BattleLayer);
	// virtual void onEnter() override;
	Player* getPlayer();
	// BasePlayer* getBasePlayer();
protected:
	cocos2d::Camera* _camera;

	Player* Player;
	int initHP;

	const float shootCD = 0.04f;
	float shootTimer;
	bool shootEnterCD;

	// Shoot Assist
	cocos2d::Sprite* shootBox;
	cocos2d::Sprite* shootLine;
	cocos2d::Vec2 boxPosition;
	float rotateAngle;

	virtual void update(float deltaTime) override;
	bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif /* BattleLayer_H_ */