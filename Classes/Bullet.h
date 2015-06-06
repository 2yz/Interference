#ifndef BULLET_H_
#define BULLET_H_

#include "BaseBullet.h"

class Bullet : public BaseBullet
{
public:
	static Bullet* create(const cocos2d::Vec2& velocity);
	explicit Bullet(const cocos2d::Vec2& velocity);
	virtual bool init() override;
protected:
	int _bulletTag;
};

#endif /* BULLET_H_ */