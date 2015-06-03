/*
* ����������
*/

#include "EnemyLayer.h"
#include "HelloWorldScene.h"
#include "BattleScene.h"
#include "EnemyUserData.h"
#include "BulletUserData.h"
#include "PlayerUserData.h"
#include "ConfigUtil.h"

USING_NS_CC;

EnemyLayer::EnemyLayer() :
visibleSize(Director::getInstance()->getVisibleSize()), visibleOrigin(Director::getInstance()->getVisibleOrigin()),
baseEnemyAppearProbability(ConfigUtil::probabilityOfBaseEnemyAppear),
deltaEnemyAppearProbability(ConfigUtil::probabilityOfDeltaEnemyAppear),
nowEnemyAppearProbability(baseEnemyAppearProbability),
bossAppeared(false), bossWarning(nullptr), bossSprite(nullptr)
{
}

EnemyLayer::~EnemyLayer()
{
}

bool EnemyLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	std::string name1 = "enemy1.png";
	std::string name2 = "enemy2.png";
	std::string name3 = "enemy3.png";
	enemyTextureName.push_back(name1);
	enemyTextureName.push_back(name2);
	enemyTextureName.push_back(name3);

	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy1"));
	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy2"));
	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy3"));

	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy1"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy2"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy3"));

	startAddEnemy();
	this->scheduleUpdate();

	bossWarning = Sprite::createWithSpriteFrameName("bossWarning.png");
	bossWarning->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	bossWarning->setScale(3.0f);
	bossWarning->setOpacity(0);
	this->addChild(bossWarning, 128);

	return true;
}

cocos2d::Sprite* EnemyLayer::getBossSprite()
{
	return this->bossSprite;
}

void EnemyLayer::addEnemySprite(float useless)
{
	auto testProbability = CCRANDOM_0_1();
	if (testProbability < nowEnemyAppearProbability)
	{
		int randomLevel = CCRANDOM_0_1() * 3;
		auto enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[randomLevel].c_str());
		int randomX = CCRANDOM_0_1()*(visibleOrigin.x + visibleSize.width);
		enemySprite->setPosition(randomX, visibleOrigin.y + visibleSize.height + enemySprite->getContentSize().height / 2);
		enemySprite->setUserData(new EnemyUserData(enemyInitHP[randomLevel]));
		this->addChild(enemySprite);
		allEnemy.pushBack(enemySprite);

		auto enemyMove = MoveTo::create(enemyFlyTime[randomLevel], Point(randomX, -enemySprite->getContentSize().height / 2));
		auto enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
		Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
		enemySprite->runAction(enemyAction);
	}
	nowEnemyAppearProbability += deltaEnemyAppearProbability;
	if (nowEnemyAppearProbability > 1) {
		this->stopAddEnemy();
		this->setBossWarningOn();
		this->addBossSprite();
	}
}

void EnemyLayer::enemyMoveFinished(Node* pSender)
{
	Sprite* enemy = static_cast<Sprite*>(pSender);
	allEnemy.eraseObject(enemy);
	delete static_cast<EnemyUserData*>(enemy->getUserData());
	this->removeChild(enemy, true);
}

void EnemyLayer::startAddEnemy()
{
	this->schedule(schedule_selector(EnemyLayer::addEnemySprite), UserDefault::getInstance()->getFloatForKey("intervalOfAddEnemy"));
}

void EnemyLayer::stopAddEnemy()
{
	this->unschedule(schedule_selector(EnemyLayer::addEnemySprite));
}

void EnemyLayer::update(float useless)
{
//	Animation* animationExplosion = AnimationCache::getInstance()->getAnimation("explosion");
//	animationExplosion->setRestoreOriginalFrame(false);
//	animationExplosion->setDelayPerUnit(0.5f / 9.0f);
//	auto actionExplosion = Animate::create(animationExplosion);
//
//	//�ж��Ƿ��Ѿ�ͨ��
//	if ((allEnemy.empty() == true) && (this->bossAppeared == true)) {
//		static_cast<CameraNode*>(this->getParent())->getEnemyBulletLayer()->bossStopShooting();
//		scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack), 1.0f);
//	}
//
//	//�����л�
//	for (Sprite* enemy : this->allEnemy) {
//		//�жϵл��Ƿ����ڱ�ը
//		if (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false) {
//			for (Sprite* bullet : static_cast<CameraNode*>(this->getParent())->getBulletLayer()->allBullet) {
//				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
//				//�ж��ӵ��Ƿ���л���ײ��֮����Ҫ�ظ��ж��Ƿ�isDeleting��Ϊ�˷�ֹ������ͷͬʱ����Ŀ�����ɳ��������bug
//				if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false)) {
//
//					//��ȡ�ӵ����˺������л�����˺�
//					if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(static_cast<BulletUserData*>(bullet->getUserData())->getDamage()) == false) {
//						enemy->stopAllActions();
//						static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
//						enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
//						//�ݻٵл���ӷ�
//						static_cast<BattleScene*>(this->getParent())->getUILayer()->addScoreBy(100);
//					}
//					//end��ȡ�ӵ����˺������л�����˺�
//
//					//������Ѫ�ı�BOSS���
//					if (this->bossAppeared == true){
//						if (static_cast<EnemyUserData*>(bossSprite->getUserData())->getHP() < (UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss") / 3 * 2) && (static_cast<EnemyUserData*>(bossSprite->getUserData())->getHP() > (UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss") / 3))){
//							bossSprite->setSpriteFrame("enemyBossBroken.png");
//						}
//						else if (static_cast<EnemyUserData*>(bossSprite->getUserData())->getHP() < (UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss") / 3)){
//							bossSprite->setSpriteFrame("enemyBossBrokenMore.png");
//						}
//					}//end������Ѫ�ı�BOSS���
//
//					//�����ӵ�
//					static_cast<CameraNode*>(this->getParent())->getBulletLayer()->bulletMoveFinished(bullet);
//				}
//				//end�ж��ӵ��Ƿ���л���ײ
//
//				//�ж��ҷ��ɻ��Ƿ���л���ײ
//				if (enemy->getBoundingBox().intersectsRect(static_cast<CameraNode*>(this->getParent())->getPlayerLayer()->getMyPlane()->getBoundingBox()) && static_cast<PlayerUserData*>(static_cast<CameraNode*>(this->getParent())->getPlayerLayer()->getMyPlane()->getUserData())->getHP() > 0) {
//					//���л������ײ�˺�
//					if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(400) == false) {
//						enemy->stopAllActions();
//						static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
//						enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
//
//						//ײ�ٵл���ӷ�
//						static_cast<BattleScene*>(this->getParent())->getUILayer()->addScoreBy(100);
//					}
//					//end���л������ײ�˺�
//
//					//���ҷ��ɻ������ײ�˺�
//					if (static_cast<PlayerUserData*>(static_cast<CameraNode*>(this->getParent())->getPlayerLayer()->getMyPlane()->getUserData())->isAliveUnderAttack(200) == false) {
//						static_cast<CameraNode*>(this->getParent())->getBulletLayer()->stopShooting();
//						static_cast<CameraNode*>(this->getParent())->getPlayerLayer()->getMyPlane()->runAction(Sequence::create(actionExplosion, NULL));
//						scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack), 1.0f);
//					}
//					//end���ҷ��ɻ������ײ�˺�
//
//					//����HPָʾ��
//					static_cast<BattleScene*>(this->getParent())->getUILayer()->updateHPIndicator();
//				}
//				//end�ж��ҷ��ɻ��Ƿ���л���ײ
//			}
//		}
//		//end�жϵл��Ƿ����ڱ�ը
//	}
//	//end�����л�
}

void EnemyLayer::addBossSprite()
{
	bossSprite = Sprite::createWithSpriteFrameName("enemyBoss.png");
	bossSprite->setPosition((visibleOrigin.x + visibleSize.width) / 2, visibleOrigin.y + visibleSize.height + bossSprite->getContentSize().height);
	bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss")));
	this->addChild(bossSprite);
	allEnemy.pushBack(bossSprite);

	FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), Point((visibleOrigin.x + visibleSize.width) / 2,
		visibleOrigin.y + visibleSize.height - 200 - bossSprite->getContentSize().height / 2));
	FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::bossStartMove, this));

	Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
	bossSprite->runAction(enemyAppearAction);

	this->bossAppeared = true;
}

void EnemyLayer::changeSceneCallBack(float useless)
{
	auto helloWorld = TransitionFade::create(2.0f, HelloWorld::createScene());
	Director::getInstance()->replaceScene(helloWorld);
}

void EnemyLayer::setBossWarningOn()
{
	Sequence* sequenceFront = Sequence::create(FadeIn::create(0.5f), FadeOut::create(1.5f), FadeIn::create(0.5f), FadeOut::create(2.0f), NULL);
	this->bossWarning->runAction(sequenceFront);
}

void EnemyLayer::bossStartMove()
{
//	Vector<FiniteTimeAction*> bossMoveBezier;
//
//	for (int i = 0; i < 10; i++) {
//		ccBezierConfig bezierConfig;
//		bezierConfig.controlPoint_1 = Point(CCRANDOM_0_1()*(visibleOrigin.x + visibleSize.width), CCRANDOM_0_1()*(visibleOrigin.y + visibleSize.height));
//		bezierConfig.controlPoint_2 = Point(CCRANDOM_0_1()*(visibleOrigin.x + visibleSize.width), CCRANDOM_0_1()*(visibleOrigin.y + visibleSize.height));
//		bezierConfig.endPosition = Point(CCRANDOM_0_1()*(visibleOrigin.x + visibleSize.width), (visibleOrigin.y + visibleSize.height) / 3 * 2 + (CCRANDOM_0_1()*(visibleOrigin.y + visibleSize.height) / 3));
//		FiniteTimeAction* tempBossMoveBezier = BezierTo::create(3.0f, bezierConfig);
//		bossMoveBezier.pushBack(tempBossMoveBezier);
//	}
//
//	Sequence* bossMoveSequence = Sequence::create(bossMoveBezier.at(0), bossMoveBezier.at(1), bossMoveBezier.at(2), bossMoveBezier.at(3), bossMoveBezier.at(4), bossMoveBezier.at(5), bossMoveBezier.at(6), bossMoveBezier.at(7), bossMoveBezier.at(8), bossMoveBezier.at(9), NULL);
//	RepeatForever* bossMoveSequenceRepeat = RepeatForever::create(bossMoveSequence);
//	bossSprite->runAction(bossMoveSequenceRepeat);
//
//	static_cast<CameraNode*>(this->getParent())->getEnemyBulletLayer()->bossStartShooting();
}