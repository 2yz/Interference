#include "BulletLayer.h"
#include "GameScene.h"
#include "BulletUserData.h"

USING_NS_CC;

BulletLayer::BulletLayer() : eachBulletDamage(UserDefault::getInstance()->getIntegerForKey("damageOfInitBullet")), nowBulletLevel(0)
{
}

bool BulletLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	bulletTextureName.push_back("bullet1.png");
	bulletTextureName.push_back("bullet2.png");
	bulletTextureName.push_back("bullet3.png");

	bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet1.png")->getTexture()));
	bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet2.png")->getTexture()));
	bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet3.png")->getTexture()));
	bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigBomb.png")->getTexture()));	//定义大招层

	this->addChild(bulletBatchNodeVector[0]);
	this->addChild(bulletBatchNodeVector[1]);
	this->addChild(bulletBatchNodeVector[2]);
	this->addChild(bulletBatchNodeVector[3]);

	this->startShooting();
	return true;
}


void BulletLayer::startShooting()
{
	this->schedule(schedule_selector(BulletLayer::addBullet), UserDefault::getInstance()->getFloatForKey("intervalOfAddBullet"));
}

void BulletLayer::stopShooting()
{
	unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::setBulletLevelUP()
{
	if (nowBulletLevel < 2) {
		this->nowBulletLevel += 1;
		this->eachBulletDamage += UserDefault::getInstance()->getIntegerForKey("damageOfDeltaWhenLevelUp");
	}
}
// TODO 大招
void BulletLayer::launchBigBomb()
{

}

// TODO 是否有必要用静态函数获取player层
void BulletLayer::addBullet(float useless)
{
	Sprite* bullet = Sprite::createWithSpriteFrameName(bulletTextureName[nowBulletLevel]);
	Point planePosition = static_cast<ControlNode*>(this->getParent())->getPlayerLayer()->getChildByName("PLAYER")->getPosition();

	Point bulletPosition = Point(planePosition.x, planePosition.y + static_cast<ControlNode*>(this->getParent())->getPlayerLayer()->getChildByName("PLAYER")->getContentSize().height);

	bullet->setPosition(bulletPosition);
	bullet->setUserData(new BulletUserData(eachBulletDamage, nowBulletLevel));
	allBullet.pushBack(bullet);
	this->bulletBatchNodeVector[nowBulletLevel]->addChild(bullet);

	float bulletFlyLenth = Director::getInstance()->getWinSize().height - bulletPosition.y + (bullet->getContentSize().height / 2);
	float bulletFlySpeed = 1000 / 1;
	float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

	// TODO 使用update绘制替代MoveTo
	FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

	auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
	bullet->runAction(bulleAction);
}

void BulletLayer::bulletMoveFinished(Node* pSender)
{
	Sprite* bullet = static_cast<Sprite*>(pSender);
	BulletUserData* bulletUserData = static_cast<BulletUserData*>(bullet->getUserData());
	int bulletLevel = bulletUserData->getBulletLevel();
	delete bulletUserData;
	allBullet.eraseObject(bullet);
	this->bulletBatchNodeVector[bulletLevel]->removeChild(bullet, true);
}
