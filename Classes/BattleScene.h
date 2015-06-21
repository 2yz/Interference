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
	BATTLE_PAUSE
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
	// CameraNode* getCameraLayer();

	// BulletLayer* getBulletLayer();
	// PlayerLayer* getPlayerLayer();
	// EnemyBulletLayer* getEnemyBulletLayer();
	// EnemyLayer* getEnemyLayer();
protected:
	// static GameBackgroundLayer* game_background_layer_;
	BattleSceneState battle_scene_state_;
	static BattleScene* battle_scene_;
	CameraNode* camera_node_;
	HUDLayer* hud_layer_;
	BattleLayer* battle_layer_;
	
	// static CameraNode* cameraNode;
	// cocos2d::Camera* camera_;
	// virtual void update(float deltaTime) override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	// static BulletLayer* bulletLayer;
	// static PlayerLayer* playerLayer;
	// static EnemyBulletLayer* enemyBulletLayer;
	// static EnemyLayer* enemyLayer;
};

#endif /* BattleScene_H_ */