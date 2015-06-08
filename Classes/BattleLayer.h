#ifndef BattleLayer_H_
#define BattleLayer_H_

#include "cocos2d.h"
#include "Player.h"
#include "TimeCoefficient.h"

class BattleLayer : public cocos2d::Layer, public TimeCoefficient
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

	Player* player;
	int initHP;

	// Shoot Assist Line
	// cocos2d::Sprite* shootBox;
	cocos2d::Vec2 mousePositionInLayer;
	cocos2d::Sprite* shootLine;
	float shootLineRotateAngle;

	virtual void update(float deltaTime) override;
	bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif /* BattleLayer_H_ */