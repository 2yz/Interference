#include "GameLayer.h"
#include "ConfigUtil.h"
#include "BulletUserData.h"
#include "EnemyUserData.h"
#include "GameScene.h"
#include "PlayerUserData.h"
#include "HelloWorldScene.h"

USING_NS_CC;

GameLayer::GameLayer() : playerPlane(nullptr), initHP(1000)
{
}

// baseEnemyAppearProbability(ConfigUtil::probabilityOfBaseEnemyAppear),
// deltaEnemyAppearProbability(ConfigUtil::probabilityOfDeltaEnemyAppear),
// nowEnemyAppearProbability(baseEnemyAppearProbability),
// bossAppeared(false), bossWarning(nullptr), bossSprite(nullptr), actionExplosion(nullptr)

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 绘制Player
	playerPlane = PlayerPlane::create();
	playerPlane->setPosition(0, 0);
	playerPlane->setUserData(new PlayerUserData(initHP));

	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(ConfigUtil::visibleSize * 2, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Point(0, 0));
	edgeSp->setPhysicsBody(body);
	addChild(edgeSp);
	edgeSp->setTag(0);

	this->addChild(playerPlane);
	this->scheduleUpdate();

	// 添加子弹批处理节点
	// bulletTextureName.push_back("bullet1.png");
	// bulletTextureName.push_back("bullet2.png");
	// bulletTextureName.push_back("bullet3.png");
	// bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet1.png")->getTexture()));
	// bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet2.png")->getTexture()));
	// bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet3.png")->getTexture()));
	// bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigBomb.png")->getTexture()));	//定义大招层
	// this->addChild(bulletBatchNodeVector[0]);
	// this->addChild(bulletBatchNodeVector[1]);
	// this->addChild(bulletBatchNodeVector[2]);
	// this->addChild(bulletBatchNodeVector[3]);
	// 
	// this->startShooting();

	// 添加敌机批处理节点
	// std::string name1 = "enemy1.png";
	// std::string name2 = "enemy2.png";
	// std::string name3 = "enemy3.png";
	// enemyTextureName.push_back(name1);
	// enemyTextureName.push_back(name2);
	// enemyTextureName.push_back(name3);
	// enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy1"));
	// enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy2"));
	// enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy3"));
	// enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy1"));
	// enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy2"));
	// enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy3"));
	// 
	// startAddEnemy();
	// this->scheduleUpdate();

	// 添加BOSS警告精灵
	// bossWarning = Sprite::createWithSpriteFrameName("bossWarning.png");
	// bossWarning->setPosition(0, 0);
	// bossWarning->setScale(3.0f);
	// bossWarning->setOpacity(0);
	// this->addChild(bossWarning, 128);

	return true;
}

void GameLayer::update(float deltaTime)
{
	// log("GameLayer::update(float deltaTime)");

	// Animation* animationExplosion = AnimationCache::getInstance()->getAnimation("explosion");
	// animationExplosion->setRestoreOriginalFrame(false);
	// animationExplosion->setDelayPerUnit(0.5f / 9.0f);
	// auto actionExplosion = Animate::create(animationExplosion);

	// 判断是否已经通关
	// if ((allEnemy.empty() == true) && (this->bossAppeared == true)) {
	// 	this->bossStopShooting();
	// 	scheduleOnce(schedule_selector(GameLayer::changeSceneCallBack), 1.0f);
	// }

	// 遍历敌机
	// for (Sprite* enemy : this->allEnemy) {
	// 	//判断敌机是否正在爆炸
	// 	if (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false) {
	// 		for (Sprite* bullet : allBullet) {
	// 			FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(GameLayer::enemyMoveFinished, this));
	// 			//判断子弹是否与敌机碰撞，之所以要重复判断是否isDeleting是为了防止两个弹头同时命中目标会造成程序崩溃的bug
	// 			if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false)) {
	// 
	// 				//读取子弹的伤害，给敌机造成伤害
	// 				if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(static_cast<BulletUserData*>(bullet->getUserData())->getDamage()) == false) {
	// 					enemy->stopAllActions();
	// 					static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
	// 					enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
	// 					//摧毁敌机后加分
	// 					static_cast<GameScene*>(this->getParent()->getParent())->getUILayer()->addScoreBy(100);
	// 				}
	// 				//end读取子弹的伤害，给敌机造成伤害
	// 
	// 				//根据损血改变BOSS外观
	// 				if (this->bossAppeared == true){
	// 					if (static_cast<EnemyUserData*>(bossSprite->getUserData())->getHP() < (UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss") / 3 * 2) && (static_cast<EnemyUserData*>(bossSprite->getUserData())->getHP() > (UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss") / 3))){
	// 						bossSprite->setSpriteFrame("enemyBossBroken.png");
	// 					}
	// 					else if (static_cast<EnemyUserData*>(bossSprite->getUserData())->getHP() < (UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss") / 3)){
	// 						bossSprite->setSpriteFrame("enemyBossBrokenMore.png");
	// 					}
	// 				}//end根据损血改变BOSS外观
	// 
	// 				//回收子弹
	// 				bulletMoveFinished(bullet);
	// 			}
	// 			//end判断子弹是否与敌机碰撞
	// 
	// 			//判断我方飞机是否与敌机碰撞
	// 			if (enemy->getBoundingBox().intersectsRect(playerPlane->getBoundingBox()) && static_cast<PlayerUserData*>(playerPlane->getUserData())->getHP() > 0) {
	// 				//给敌机造成碰撞伤害
	// 				if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(400) == false) {
	// 					enemy->stopAllActions();
	// 					static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
	// 					enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
	// 
	// 					//撞毁敌机后加分
	// 					static_cast<GameScene*>(this->getParent())->getUILayer()->addScoreBy(100);
	// 				}
	// 				//end给敌机造成碰撞伤害
	// 
	// 				//给我方飞机造成碰撞伤害
	// 				if (static_cast<PlayerUserData*>(playerPlane->getUserData())->isAliveUnderAttack(200) == false) {
	// 					stopShooting();
	// 					playerPlane->runAction(Sequence::create(actionExplosion, NULL));
	// 					scheduleOnce(schedule_selector(GameLayer::changeSceneCallBack), 1.0f);
	// 				}
	// 				//end给我方飞机造成碰撞伤害
	// 
	// 				//更新HP指示器
	// 				static_cast<GameScene*>(this->getParent())->getUILayer()->updateHPIndicator();
	// 			}
	// 			//end判断我方飞机是否与敌机碰撞
	// 		}
	// 	}
	// 	//end判断敌机是否正在爆炸
	// }
	//end遍历敌机

	// Animation* animationExplosion = AnimationCache::getInstance()->getAnimation("explosion");
	// animationExplosion->setRestoreOriginalFrame(false);
	// animationExplosion->setDelayPerUnit(0.5f / 9.0f);
	// actionExplosion = Animate::create(animationExplosion);

	// Sprite* myPlane = playerPlane;
	// for (Sprite* bullet : this->allEnemyBullet) {
	// 	if (bullet->getBoundingBox().intersectsRect(playerPlane->getBoundingBox())) {
	// 
	// 		if (static_cast<PlayerUserData*>(playerPlane->getUserData())->isAliveUnderAttack(200) == false){
	// 			//更新HP指示器
	// 			static_cast<GameScene*>(this->getParent())->getUILayer()->updateHPIndicator();
	// 			static_cast<CameraNode*>(this->getParent())->getBulletLayer()->stopShooting();
	// 			playerPlane->runAction(Sequence::create(actionExplosion, NULL));
	// 			scheduleOnce(schedule_selector(GameLayer::changeSceneCallBack), 1.0f);
	// 			this->bossStopShooting();
	// 			return;
	// 		}
	// 		else{
	// 			//更新HP指示器
	// 			static_cast<GameScene*>(this->getParent())->getUILayer()->updateHPIndicator();
	// 		}
	// 		bossBulletMoveFinished(bullet);
	// 	}
	// }
}

PlayerPlane* GameLayer::getPlayerPlane()
{
	return playerPlane;
}

// void GameLayer::startShooting()
// {
// 	this->schedule(schedule_selector(GameLayer::addBullet), ConfigUtil::intervalOfAddBullet);
// }
// 
// void GameLayer::stopShooting()
// {
// 	unschedule(schedule_selector(GameLayer::addBullet));
// }
// 
// void GameLayer::addBullet(float useless)
// {
// 	if (nowBulletLevel < 2) {
// 		this->nowBulletLevel += 1;
// 		this->eachBulletDamage += UserDefault::getInstance()->getIntegerForKey("damageOfDeltaWhenLevelUp");
// 	}
// }
// 
// void GameLayer::setBulletLevelUP()
// {
// 	Sprite* bullet = Sprite::createWithSpriteFrameName(bulletTextureName[nowBulletLevel]);
// 	Point planePosition = playerPlane->getPosition();
// 
// 	Point bulletPosition = Point(planePosition.x, planePosition.y + playerPlane->getContentSize().height);
// 
// 	bullet->setPosition(bulletPosition);
// 	bullet->setUserData(new BulletUserData(eachBulletDamage, nowBulletLevel));
// 	allBullet.pushBack(bullet);
// 	this->bulletBatchNodeVector[nowBulletLevel]->addChild(bullet);
// 
// 	float bulletFlyLenth = Director::getInstance()->getWinSize().height - bulletPosition.y + (bullet->getContentSize().height / 2);
// 	float bulletFlySpeed = 1000 / 1;
// 	float bulletFltTime = bulletFlyLenth / bulletFlySpeed;
// 
// 	// TODO 使用update绘制替代MoveTo
// 	FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height / 2));
// 	FiniteTimeAction* bulletRemove = CallFuncN::create(CC_CALLBACK_1(GameLayer::bulletMoveFinished, this));
// 
// 	auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
// 	bullet->runAction(bulleAction);
// }

// void GameLayer::launchBigBomb()
// {
// }
// 
// void GameLayer::bulletMoveFinished(Node* pSender)
// {
// 	Sprite* bullet = static_cast<Sprite*>(pSender);
// 	BulletUserData* bulletUserData = static_cast<BulletUserData*>(bullet->getUserData());
// 	int bulletLevel = bulletUserData->getBulletLevel();
// 	delete bulletUserData;
// 	allBullet.eraseObject(bullet);
// 	this->bulletBatchNodeVector[bulletLevel]->removeChild(bullet, true);
// }
// 
// void GameLayer::addEnemySprite(float useless)
// {
// 	auto testProbability = CCRANDOM_0_1();
// 	if (testProbability < nowEnemyAppearProbability)
// 	{
// 		int randomLevel = CCRANDOM_0_1() * 3;
// 		auto enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[randomLevel].c_str());
// 		// int randomX = CCRANDOM_0_1()*(ConfigUtil::visibleOrigin.x + ConfigUtil::visibleSize.width);
// 		int randomX = random(-ConfigUtil::visibleWidth / 2, ConfigUtil::visibleWidth / 2);
// 		enemySprite->setPosition(randomX, ConfigUtil::visibleHeight / 2 + enemySprite->getContentSize().height / 2);
// 		enemySprite->setUserData(new EnemyUserData(enemyInitHP[randomLevel]));
// 		this->addChild(enemySprite);
// 		allEnemy.pushBack(enemySprite);
// 
// 		auto enemyMove = MoveTo::create(enemyFlyTime[randomLevel], Point(randomX, -enemySprite->getContentSize().height / 2));
// 		auto enemyRemove = CallFuncN::create(CC_CALLBACK_1(GameLayer::enemyMoveFinished, this));
// 		Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
// 		enemySprite->runAction(enemyAction);
// 	}
// 	nowEnemyAppearProbability += deltaEnemyAppearProbability;
// 	if (nowEnemyAppearProbability > 1) {
// 		this->stopAddEnemy();
// 		this->setBossWarningOn();
// 		this->addBossSprite();
// 	}
// }
// 
// void GameLayer::enemyMoveFinished(Node* pSender)
// {
// 	Sprite* enemy = static_cast<Sprite*>(pSender);
// 	allEnemy.eraseObject(enemy);
// 	delete static_cast<EnemyUserData*>(enemy->getUserData());
// 	this->removeChild(enemy, true);
// }
// 
// void GameLayer::startAddEnemy()
// {
// 	this->schedule(schedule_selector(GameLayer::addEnemySprite), UserDefault::getInstance()->getFloatForKey("intervalOfAddEnemy"));
// }
// 
// void GameLayer::stopAddEnemy()
// {
// 	this->unschedule(schedule_selector(GameLayer::addEnemySprite));
// }
// 
// void GameLayer::addBossSprite()
// {
// 	bossSprite = Sprite::createWithSpriteFrameName("enemyBoss.png");
// 	bossSprite->setPosition(0, ConfigUtil::visibleHeight/2 + bossSprite->getContentSize().height/2);
// 	bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss")));
// 	this->addChild(bossSprite);
// 	allEnemy.pushBack(bossSprite);
// 
// 	FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), 
// 		Point(0, ConfigUtil::visibleHeight / 2 - 200 - bossSprite->getContentSize().height / 2));
// 	FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(GameLayer::bossStartMove, this));
// 
// 	Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
// 	bossSprite->runAction(enemyAppearAction);
// 
// 	this->bossAppeared = true;
// }
// 
// void GameLayer::changeSceneCallBack(float useless)
// {
// 	auto helloWorld = TransitionFade::create(2.0f, HelloWorld::createScene());
// 	Director::getInstance()->replaceScene(helloWorld);
// }
// 
// void GameLayer::setBossWarningOn()
// {
// 	Sequence* sequenceFront = Sequence::create(FadeIn::create(0.5f), FadeOut::create(1.5f), FadeIn::create(0.5f), FadeOut::create(2.0f), NULL);
// 	this->bossWarning->runAction(sequenceFront);
// }
// 
// void GameLayer::bossStartMove()
// {
// 	Vector<FiniteTimeAction*> bossMoveBezier;
// 
// 	for (int i = 0; i < 10; i++) {
// 		ccBezierConfig bezierConfig;
// 		bezierConfig.controlPoint_1 = Point(random(-ConfigUtil::visibleWidth/2,ConfigUtil::visibleWidth/2), random(-ConfigUtil::visibleHeight/2,ConfigUtil::visibleHeight/2));
// 		bezierConfig.controlPoint_2 = Point(random(-ConfigUtil::visibleWidth / 2, ConfigUtil::visibleWidth / 2), random(-ConfigUtil::visibleHeight / 2, ConfigUtil::visibleHeight / 2));
// 		bezierConfig.endPosition = Point(random(-ConfigUtil::visibleWidth / 2, ConfigUtil::visibleWidth / 2), ConfigUtil::visibleHeight / 2 / 3 * 2 + random(-ConfigUtil::visibleHeight / 2, ConfigUtil::visibleHeight / 2 / 3));
// 		FiniteTimeAction* tempBossMoveBezier = BezierTo::create(3.0f, bezierConfig);
// 		bossMoveBezier.pushBack(tempBossMoveBezier);
// 	}
// 
// 	Sequence* bossMoveSequence = Sequence::create(bossMoveBezier.at(0), bossMoveBezier.at(1), bossMoveBezier.at(2), bossMoveBezier.at(3), bossMoveBezier.at(4), bossMoveBezier.at(5), bossMoveBezier.at(6), bossMoveBezier.at(7), bossMoveBezier.at(8), bossMoveBezier.at(9), NULL);
// 	RepeatForever* bossMoveSequenceRepeat = RepeatForever::create(bossMoveSequence);
// 	bossSprite->runAction(bossMoveSequenceRepeat);
// 
// 	bossStartShooting();
// }
// 
// cocos2d::Sprite* GameLayer::getBossSprite()
// {
// 	return this->bossSprite;
// }
// 
// void GameLayer::bossStartShooting()
// {
// 	this->schedule(schedule_selector(GameLayer::addBossBulletSet), UserDefault::getInstance()->getFloatForKey("intervalOfAddEnemyBullet"));
// 	this->scheduleUpdate();
// }
// 
// void GameLayer::bossStopShooting()
// {
// 	this->unschedule(schedule_selector(GameLayer::addBossBulletSet));
// 	this->unscheduleUpdate();
// }
// 
// void GameLayer::addBossBulletSet(float useless)
// {
// 	Sprite* bulletSet = Sprite::createWithSpriteFrameName("enemyBulletSet.png");
// 
// 	Point bossPosition = bossSprite->getPosition();
// 	bulletSet->setPosition(bossPosition);
// 	allEnemyBullet.pushBack(bulletSet);
// 	this->addChild(bulletSet);
// 
// 	FiniteTimeAction* bulletSetMove = MoveTo::create(2, Point(-ConfigUtil::visibleWidth + CCRANDOM_0_1() * ConfigUtil::visibleWidth*2, -bulletSet->getContentSize().height / 2));
// 	FiniteTimeAction* bulletSetRemove = CallFuncN::create(CC_CALLBACK_1(GameLayer::bossBulletMoveFinished, this));
// 	Sequence* bulletSetSequence = Sequence::create(bulletSetMove, bulletSetRemove, NULL);
// 	bulletSet->runAction(bulletSetSequence);
// }
// 
// void GameLayer::bossBulletMoveFinished(Node* pSender)
// {
// 	Sprite* bullet = static_cast<Sprite*>(pSender);
// 	this->allEnemyBullet.eraseObject(bullet);
// 	this->removeChild(bullet);
// }