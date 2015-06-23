#ifndef LOGOSCENE_H_
#define LOGOSCENE_H_

#include "cocos2d.h"

enum class LoadState
{
	NA,
	LOADING,
	LOADED
};

enum class AnimationState
{
	NA,
	FADE_IN,
	WAIT_LOADING,
	FADE_OUT
};

class LoadScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(LoadScene);
	LoadScene();
	virtual bool init() override;
	virtual void onEnter() override;
	void textureCallBack(cocos2d::Texture2D *texture);
	virtual void update(float delta_time) override;
protected:
	LoadState load_state_;
	AnimationState animation_state_;
	int loaded_num_;
	int total_num_;
	cocos2d::Sprite* logo_;
	std::vector<std::string> texture_vector_;

};

#endif /* LOGOSCENE_H_ */