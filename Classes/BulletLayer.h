#ifndef BULLETLAYER_H_
#define BULLETLAYER_H_

#include "cocos2d.h"

class BulletLayer : public cocos2d::Layer{
public:
	cocos2d::Vector<cocos2d::Sprite*> allBullet;
	BulletLayer();
	virtual bool init() override;
	CREATE_FUNC(BulletLayer);
	void startShooting();
	void stopShooting();
	void addBullet(float useless);
	void setBulletLevelUP();
	void launchBigBomb();
	void bulletMoveFinished(Node* pSender);
private:
	int eachBulletDamage;
	int nowBulletLevel;
	std::vector<std::string> bulletTextureName;
	std::vector<cocos2d::SpriteBatchNode*> bulletBatchNodeVector;
	
};

#endif /* BULLETLAYER_H_ */