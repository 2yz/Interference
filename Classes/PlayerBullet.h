#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_

#include "BaseBullet.h"

class PlayerBullet : public BaseBullet
{
public:
	explicit PlayerBullet(cocos2d::Vec2& velocity);
	// CREATE_FUNC(PlayerBullet);
	static PlayerBullet* create(cocos2d::Vec2& velocity);

	virtual bool init() override;
};



#endif /* PLAYERBULLET_H_ */