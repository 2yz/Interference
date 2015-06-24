#ifndef BASEBULLET_H_
#define BASEBULLET_H_

#include "BaseObject.h"

class BaseBullet : public BaseObject
{
public:
	BaseBullet();
	virtual bool init() override;
	virtual void onDestroy() override;
	virtual void onContact(Message& message) override;
protected:
	cocos2d::Vec2 velocity_vec_;
	float damage_;
	int bullet_parent_;
};

#endif /* BASEBULLET_H_ */