#ifndef BASEBULLET_H_
#define BASEBULLET_H_

#include "BaseObject.h"

class BaseBullet : public BaseObject
{
public:
	BaseBullet(int bulletParent=0);
	virtual bool init() override;
	virtual void onDestory() override;
	virtual void onContact(BaseObject* contactNode) override;
protected:
	cocos2d::Vec2 velocityVec;
	float _damage;
	int _bulletParent;
};

#endif /* BASEBULLET_H_ */