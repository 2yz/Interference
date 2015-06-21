#ifndef CAMERANODE_H_
#define CAMERANODE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "BattleLayer.h"


class CameraNode : public cocos2d::Node
{
public:
	CREATE_FUNC(CameraNode);
	CameraNode();
	virtual ~CameraNode();
	virtual bool init() override;
	void setListener();
	static cocos2d::Camera* getCamera();
	void addBattleLayer(BattleLayer* battle_layer);
	void removeBattleLayer();
	// virtual void onEnter() override;
	// virtual void onExit() override;
	// void updateCamera(float delta_time);
	virtual void update(float delta_time) override;
protected:
	static cocos2d::Camera* camera_;
	GameBackgroundLayer* game_background_layer_;
	BattleLayer* battle_layer_;
	float delta_time_;
};

#endif /* CAMERANODE_H_ */