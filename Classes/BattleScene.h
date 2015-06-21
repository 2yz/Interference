#ifndef BattleScene_H_
#define BattleScene_H_

#include "cocos2d.h"
#include "HUDLayer.h"
#include "BattleLayer.h"
#include "MenuLayer.h"
#include "CameraNode.h"
#include "MouseLayer.h"

enum BattleSceneState
{
	MENU,
	BATTLE,
	BATTLE_PAUSE,
	BATTLE_RESULT
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
	void openMenu();
	void startBattle();
	void pauseBattle();
	void resumeBattle();
protected:
	static BattleScene* battle_scene_;
	BattleSceneState battle_scene_state_;
	CameraNode* camera_node_;
	HUDLayer* hud_layer_;
	BattleLayer* battle_layer_;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif /* BattleScene_H_ */