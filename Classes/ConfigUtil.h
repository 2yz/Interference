#ifndef CONFIGUTIL_H_
#define CONFIGUTIL_H_

#include "cocos2d.h"


#define PLAYER_TAG 1
#define PLAYER_GROUP 1
#define PLAYER_CONTACT_MASK 0x0000000F
#define PLAYER_COLLISION_MASK 0x0000000F
#define PLAYER_CATEGORY_MASK 0x0000000F

#define ENEMY_TAG 2

#define BULLET_TAG -2
#define BULLET_GROUP -2
#define BULLET_CONTACT_MASK 0x0000F000
#define BULLET_COLLISION_MASK 0x0000F000
#define BULLET_CATEGORY_MASK 0x0000F000
// Bullet Parent
#define PLAYER 1
#define ENEMY 2

#define EDGE_TAG 10
#define EDGE_GROUP 1

class ConfigUtil
{
public:
	static cocos2d::Size visibleSize;
	static cocos2d::Vec2 visibleOrigin;
	static float visibleWidth;
	static float visibleHeight;
	static float battleSceneWidth;
	static float battleSceneHeight;
	static float intervalOfAddBullet;
	static float intervalOfAddEnemy;
	static float intervalOfAddEnemyBullet;
	
	static float probabilityOfBaseEnemyAppear;
	static float probabilityOfDeltaEnemyAppear;
};

#endif /* CONFIGUTIL_H_ */