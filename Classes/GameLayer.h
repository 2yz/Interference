#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "cocos2d.h"
#include "PlayerPlane.h"

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	virtual bool init() override;
	CREATE_FUNC(GameLayer);
	PlayerPlane* getPlayerPlane();
	
protected:
	static PlayerPlane* playerPlane;
	
	int initHP;

	// cocos2d::Vector<cocos2d::Sprite*> allBullet;
	// int eachBulletDamage;
	// int nowBulletLevel;
	// std::vector<std::string> bulletTextureName;
	// std::vector<cocos2d::SpriteBatchNode*> bulletBatchNodeVector;
	// 
	// float  baseEnemyAppearProbability;
	// float deltaEnemyAppearProbability;
	// float nowEnemyAppearProbability;
	// std::vector<std::string> enemyTextureName;
	// std::vector<int> enemyFlyTime;
	// std::vector<int> enemyInitHP;
	// cocos2d::Vector<cocos2d::Sprite*> allEnemy;
	// bool bossAppeared;
	// cocos2d::Sprite* bossWarning;
	// cocos2d::Sprite* bossSprite;
	// 
	// cocos2d::Animate* actionExplosion;
	// cocos2d::Vector<cocos2d::Sprite*> allEnemyBullet;
	// 
	virtual void update(float deltaTime) override;
	// 
	// void startShooting();
	// void stopShooting();
	// void addBullet(float useless);
	// void setBulletLevelUP();
	// void launchBigBomb();
	// void bulletMoveFinished(Node* pSender);
	// 
	// void addEnemySprite(float useless);
	// void enemyMoveFinished(Node* pSender);
	// void startAddEnemy();
	// void stopAddEnemy();
	// void addBossSprite();
	// void changeSceneCallBack(float useless);
	// void setBossWarningOn();
	// void bossStartMove();
	// cocos2d::Sprite* getBossSprite();
	// 
	// void bossStartShooting();
	// void bossStopShooting();
	// void addBossBulletSet(float useless);
	// void bossBulletMoveFinished(Node* pSender);
};

#endif /* GAMELAYER_H_ */