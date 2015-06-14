#ifndef BULLET_H_
#define BULLET_H_

#include "BaseBullet.h"

class Bullet : public BaseBullet
{
public:
	static Bullet* create(int bulletParent, const cocos2d::Vec2& unitVelocity);
	explicit Bullet(int bulletParent, const cocos2d::Vec2& unitVelocity);
	virtual bool init() override;
	virtual void initMessage() override;
	virtual void onEnter() override;
};

#endif /* BULLET_H_ */