#ifndef BattleLayer_H_
#define BattleLayer_H_

#include "cocos2d.h"
#include "Player.h"
#include "TimeCoefficient.h"
#include "Block.h"
#include "BaseEnemy.h"

enum BattleState
{
	BEGIN,
	ROUND1,
	ROUND2,
	BOSS,
	END,
	LOSS,
	WIN
};

class BattleLayer : public cocos2d::Layer, public TimeCoefficient
{
public:
	BattleLayer();
	virtual ~BattleLayer();
	virtual bool init() override;
	void setListener();
	virtual void onEnter() override;
	virtual void onExit() override;
	void sendDestroyEvent();
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
	void sendBattleEvent(int event_data);
	void enableShootLine();
	void disableShootLine();
	void updateShootLine(float delta_time);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
	virtual void update(float delta_time) override;
	virtual void updateStateMachine(float delta_time) = 0;
	virtual void setState(BattleState battle_state) = 0;
	virtual void enterState(BattleState battle_state) = 0;
	virtual void exitState(BattleState battle_state) = 0;
protected:
	static BattleLayer* battle_layer_;
	float timer_;
	Player* player_;
	cocos2d::Vector<BaseEnemy*> enemy_;
	cocos2d::Vector<Block*> block_;
	cocos2d::Sprite* shoot_line_;
	bool paused_;
	int background_music_;
	BattleState battle_state_;
	float state_timer_;
	float state_count_;
};

#endif /* BattleLayer_H_ */