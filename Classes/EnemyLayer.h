/*
* 此类已弃用
*/

#ifndef ENEMYLAYER_H_
#define ENEMYLAYER_H_

#include <string>
#include <vector>
#include "cocos2d.h"

class EnemyLayer : public cocos2d::Layer{
public:
	EnemyLayer();
	virtual ~EnemyLayer();
	virtual bool init() override;
	CREATE_FUNC(EnemyLayer);
	cocos2d::Sprite* getBossSprite();
private:
	const cocos2d::Size visibleSize;
	const cocos2d::Vec2 visibleOrigin;
	float  baseEnemyAppearProbability;
	float deltaEnemyAppearProbability;	
	float nowEnemyAppearProbability;
	std::vector<std::string> enemyTextureName;
	std::vector<int> enemyFlyTime;
	std::vector<int> enemyInitHP;
	cocos2d::Vector<cocos2d::Sprite*> allEnemy;
	bool bossAppeared;
	cocos2d::Sprite* bossWarning;
	cocos2d::Sprite* bossSprite;
	void addEnemySprite(float useless);
	void enemyMoveFinished(Node* pSender);
	void startAddEnemy();
	void stopAddEnemy();
	void update(float useless) override;
	void addBossSprite();
	void changeSceneCallBack(float useless);
	void setBossWarningOn();
	void bossStartMove();

};

#endif /* ENEMYLAYER_H_ */