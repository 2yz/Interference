#ifndef BATTLECAMERA_H_
#define BATTLECAMERA_H_

#include "cocos2d.h"
#include "BackgroundManager.h"
#include "BattleManager.h"


class BattleCamera : public cocos2d::Node
{
public:
	CREATE_FUNC(CameraManager);
	CameraManager();
	virtual ~CameraManager();
	virtual bool init() override;
	void setListener();
	static cocos2d::Camera* getCamera();
	void addBattleManager(BattleManager* battle_manager);
	void removeBattleManager();
	// virtual void onEnter() override;
	// virtual void onExit() override;
	// void updateCamera(float delta_time);
	virtual void update(float delta_time) override;
protected:
	static cocos2d::Camera* camera_;
	BackgroundManager* game_background_layer_;
	BattleManager* battle_manager_;
	float delta_time_;
};

#endif /* BATTLECAMERA_H_ */