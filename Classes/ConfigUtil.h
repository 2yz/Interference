#ifndef CONFIGUTIL_H_
#define CONFIGUTIL_H_

#include "cocos2d.h"

#define PLAYER_CONTACT_MASK 0x00000FFF
#define PLAYER_COLLISION_MASK 0x00000FFF
#define PLAYER_CATEGORY_MASK 0x00000FFF

#define BULLET_CONTACT_MASK 0x0000F000
#define BULLET_COLLISION_MASK 0x0000F000
#define BULLET_CATEGORY_MASK 0x0000F000

class ConfigUtil
{
public:
	static cocos2d::Size visibleSize;
	static cocos2d::Vec2 visibleOrigin;
	static float visibleWidth;
	static float visibleHeight;
	static float intervalOfAddBullet;
	static float intervalOfAddEnemy;
	static float intervalOfAddEnemyBullet;
	
	static float probabilityOfBaseEnemyAppear;
	static float probabilityOfDeltaEnemyAppear;
};

#endif /* CONFIGUTIL_H_ */