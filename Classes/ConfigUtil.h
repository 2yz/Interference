#ifndef CONFIGUTIL_H_
#define CONFIGUTIL_H_

#include "cocos2d.h"

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
};

#endif /* CONFIGUTIL_H_ */