#ifndef BackgroundManager_H_
#define BackgroundManager_H_

#include "cocos2d.h"

class BackgroundManager : public cocos2d::Layer
{
public:
	CREATE_FUNC(BackgroundManager);
	virtual bool init() override;
	virtual void onEnter() override;
};

#endif /* BackgroundManager_H_ */