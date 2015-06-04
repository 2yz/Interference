#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_

#include "BaseBullet.h"

class PlayerBullet : public BaseBullet
{
public:
	explicit PlayerBullet(cocos2d::Vec2& velocity);
	virtual bool init() override;
	virtual bool initWithSpriteFrameName(const std::string& spriteFrameName) override;
	static PlayerBullet* create(cocos2d::Vec2& velocity,const std::string& spriteFrameName = "bullet.png");
protected:
	cocos2d::Vec2 velocity;
};

#endif /* PLAYERBULLET_H_ */