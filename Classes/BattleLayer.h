#ifndef BattleLayer_H_
#define BattleLayer_H_

#include "cocos2d.h"
#include "Player.h"
#include "TimeCoefficient.h"

enum BattleState
{
	BEGIN,
	ROUND1,
	ROUND2,
	BOSS
};

class BattleLayer : public cocos2d::Layer, public TimeCoefficient
{
public:
	CREATE_FUNC(BattleLayer);
	BattleLayer();
	virtual ~BattleLayer();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	static BattleLayer* getInstance();
	virtual void addChild(Node * child) override;
	virtual void addChild(Node * child, int localZOrder) override;
	void addLayerChild(Node * child);
	virtual void removeChild(Node* child, bool cleanup = true) override;
	virtual void removeAllChildrenWithCleanup(bool cleanup) override;
	void pauseLayer();
	void resumeLayer();
	bool isPaused();
	cocos2d::Vec2 getPlayerDirection();
	cocos2d::Vec2 getPlayerPosition();
	void enableShootLine();
	void disableShootLine();
	virtual void update(float deltaTime) override;
	void updateStateMachine(float deltaTime);
	void setState(BattleState battle_state);
	void enterState(BattleState battle_state);
	void exitState(BattleState battle_state);
	void updateShootLine(float deltaTime);
protected:
	static BattleLayer* battle_layer_;
	float _timer;
	
	Player* _player;
	cocos2d::Vector<Node*> _enemy;
	cocos2d::Vector<Node*> _block;
	cocos2d::Sprite* shootLine; // Shoot Assist Line
	bool paused_;
	int background_music;
	BattleState battle_state_;
	float state_timer_;
	// float state_cd_limit_;
	// bool state_cd_;
	// int state_times_;
	// int state_times_limit_;

	//cocos2d::Vec2 mousePositionInLayer;
	//float shootLineRotateAngle;
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
};

#endif /* BattleLayer_H_ */