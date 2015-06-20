#ifndef BattleLayer_H_
#define BattleLayer_H_

#include "cocos2d.h"
#include "Player.h"
#include "TimeCoefficient.h"

class BattleLayer : public cocos2d::Layer, public TimeCoefficient
{
public:
	CREATE_FUNC(BattleLayer);
	BattleLayer();
	virtual ~BattleLayer();
	virtual bool init() override;
	static BattleLayer* getInstance();
	virtual void addChild(Node * child) override;
	virtual void addChild(Node * child, int localZOrder) override;
	void addLayerChild(Node * child);
	virtual void removeChild(Node* child, bool cleanup = true) override;
	virtual void removeAllChildrenWithCleanup(bool cleanup) override;
	cocos2d::Vec2 getPlayerDirection();
	cocos2d::Vec2 getPlayerPosition();
	void enableShootLine();
	void disableShootLine();
	void playerStateMachine();
	void enemyStateMachine();
	void updateCamera(float deltaTime);
	void updateShootLine(float deltaTime);
	virtual void update(float deltaTime) override;
protected:
	static BattleLayer* battle_layer_;
	float _timer;
	cocos2d::Camera* camera_;
	Player* _player;
	cocos2d::Vector<Node*> _enemy;
	cocos2d::Vector<Node*> _block;
	cocos2d::Sprite* shootLine; // Shoot Assist Line
	//cocos2d::Vec2 mousePositionInLayer;
	//float shootLineRotateAngle;

	
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void addEnemy(float deltaTime);
};

#endif /* BattleLayer_H_ */