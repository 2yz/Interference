#ifndef ENEMYBULLETLAYER_H_
#define ENEMYBULLETLAYER_H_

#include "cocos2d.h"

class EnemyBulletLayer : public cocos2d::Layer{
public:
	EnemyBulletLayer();
	virtual bool init() override;
	CREATE_FUNC(EnemyBulletLayer);
	void bossStartShooting();
	void bossStopShooting();
private:
	const cocos2d::Size visibleSize;
	const cocos2d::Vec2 visibleOrigin;
	cocos2d::Animate* actionExplosion;
	cocos2d::Vector<cocos2d::Sprite*> allEnemyBullet;
	void addBossBulletSet(float useless);
	void bossBulletMoveFinished(Node* pSender);
	void update(float useless);
	void changeSceneCallBack(float useless);
};

#endif /* ENEMYBULLETLAYER_H_ */