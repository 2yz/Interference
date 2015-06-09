#ifndef BULLET_H_
#define BULLET_H_

#include "BaseBullet.h"

class Bullet : public BaseBullet
{
public:
	static Bullet* create(const cocos2d::Vec2& unitVelocity, int bulletParent);
	explicit Bullet(const cocos2d::Vec2& unitVelocity, int bulletParent);
	virtual bool init() override;
};

#endif /* BULLET_H_ */