#include "PlayerBullet.h"

USING_NS_CC;

PlayerBullet::PlayerBullet(cocos2d::Vec2& velocity)
{
	physicsBody->setVelocity(velocity);
}

PlayerBullet* PlayerBullet::create(cocos2d::Vec2& velocity)
{
	PlayerBullet *pRet = new(std::nothrow) PlayerBullet(velocity);
	CALL_INIT();
}

bool PlayerBullet::init()
{
	if (!BaseBullet::init())
	{
		return false;
	}
	bullet->setSpriteFrame("bullet.png");
}