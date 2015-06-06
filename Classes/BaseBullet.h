#ifndef BASEBULLET_H_
#define BASEBULLET_H_

#include "BaseObject.h"

class BaseBullet : public BaseObject
{
public:
	BaseBullet();
	virtual bool init() override;
protected:
	cocos2d::Vec2 velocityVec;
	int damage;
};

#endif /* BASEBULLET_H_ */