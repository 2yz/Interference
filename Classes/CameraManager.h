#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include "cocos2d.h"
#include "BackgroundManager.h"
#include "BattleManager.h"


class CameraManager : public cocos2d::Node
{
public:
	CREATE_FUNC(CameraManager);
	CameraManager();
	virtual ~CameraManager();
	virtual bool init() override;
	void setListener();
	static cocos2d::Camera* getCamera();
	void setCameraPosition(cocos2d::Vec2 position);
	void addBattleManager(BattleManager* battle_manager);
	void removeBattleManager();
	void addBackgroundManager(BackgroundManager* background_manager);
	void removeBackgroundManager();
	// virtual void onEnter() override;
	// virtual void onExit() override;
	// void updateCamera(float delta_time);
	virtual void update(float delta_time) override;
protected:
	float delta_time_;
	static cocos2d::Camera* camera_;
	BackgroundManager* background_manager_;
	BattleManager* battle_manager_;
};

#endif /* CAMERAMANAGER_H_ */