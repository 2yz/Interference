#ifndef BASEBULLET_H_
#define BASEBULLET_H_

#include "BaseObject.h"

class BaseBullet : public BaseObject
{
public:
	BaseBullet();
	virtual bool init() override;
	virtual void onDestroy() override;
	virtual bool onContact(BaseObject* contactNode) override;
protected:
	cocos2d::Vec2 _velocityVec;
	float _damage;
	int _bulletParent;
};

#endif /* BASEBULLET_H_ */