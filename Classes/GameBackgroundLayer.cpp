#include "GameBackgroundLayer.h"
#include "ConfigUtil.h"

USING_NS_CC;

bool GameBackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	background1 = Sprite::createWithSpriteFrameName("img_bg_1.jpg");
	// background1->setAnchorPoint(Vec2(0.5f,0.5f));
	background1->setScale(2);
	this->addChild(background1);

	background2 = Sprite::createWithSpriteFrameName("img_bg_1.jpg");
	// background2->setAnchorPoint(Vec2(0.5f, 0.5f));
	background2->setScale(2);
	this->addChild(background2);

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		[&](Ref* sender){
		Director::getInstance()->end();
	});
	closeItem->setPosition(Vec2(ConfigUtil::visibleWidth / 2 - closeItem->getContentSize().width / 2, -ConfigUtil::visibleHeight / 2 + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto closemenu = Menu::create(closeItem, NULL);
	closemenu->setPosition(Vec2::ZERO);
	this->addChild(closemenu, 1);

	// visibleSize = Director::getInstance()->getVisibleSize();

	scheduleUpdate();

	return true;
}

void GameBackgroundLayer::update(float useless)
{
	// log("Background X: %f Y: %f", this->getPositionX(), this->getPositionY());
	background1->setPositionY(background1->getPositionY() - UserDefault::getInstance()->getFloatForKey("BackgroundScorllSpeed"));
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height * 2 - UserDefault::getInstance()->getFloatForKey("BackgroundScorllSpeed"));
	if (background2->getPositionY() < 0){
		background1->setPositionY(0);
	}
}
