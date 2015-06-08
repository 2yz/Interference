#include "GameBackgroundLayer.h"
#include "ConfigUtil.h"

USING_NS_CC;

bool GameBackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	background1 = Sprite::create("img_bg_test.jpg");
	background1->setPosition(ConfigUtil::battleSceneWidth / 2, ConfigUtil::battleSceneHeight / 2);
	this->addChild(background1);
	return true;
}

