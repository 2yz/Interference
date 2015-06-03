#ifndef BASEBULLET_H_
#define BASEBULLET_H_

#include "BaseObject.h"

class BaseBullet : public BaseObject
{
public:
	explicit BaseBullet(cocos2d::Size size = cocos2d::Size(15.0f, 15.0f));
	virtual bool init() override;
protected:
	cocos2d::Sprite* bullet;
	virtual void onEnter() override;
};

#endif /* BASEBULLET_H_ */