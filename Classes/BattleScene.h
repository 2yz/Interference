#ifndef BattleScene_H_
#define BattleScene_H_

#include "cocos2d.h"
#include "HUDLayer.h"
#include "BattleManager.h"
#include "MenuLayer.h"
#include "CameraManager.h"
#include "MouseLayer.h"
#include "ResultLayer.h"
#include "PauseLayer.h"

enum class SceneState : unsigned int
{
	NA,
	INITIAL,
	MENU,
	BATTLE,
	EXIT
};

enum class BattleState : unsigned int
{
	NA,
	BATTLE_ON,
	BATTLE_PAUSE,
	BATTLE_RESULT_WIN,
	BATTLE_RESULT_LOSS
};

class BattleScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(BattleScene);
	BattleScene();
	virtual ~BattleScene();
	virtual bool init() override;
	virtual void onEnter() override;
	void setListener();
	static BattleScene* getInstance();
	HUDLayer* getHUDLayer();
	// virtual void update(float delta_time) override;
	// void updateStateMachine(float delta_time);
	void setSceneState(SceneState scene_state);
	void enterSceneState(SceneState scene_state);
	void exitSceneState();
	void setBattleState(BattleState battle_state);
	void enterBattleState(BattleState battle_state);
	void exitBattleState();
protected:
	static BattleScene* battle_scene_;
	SceneState scene_state_;
	BattleState battle_state_;
	MenuLayer* menu_layer_;
	CameraManager* camera_node_;
	HUDLayer* hud_layer_;
	BattleManager* battle_layer_;
	ResultLayer* result_layer_;
	PauseLayer* pause_layer_;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif /* BattleScene_H_ */