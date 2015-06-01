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
	this->addChild(background1);
	return true;
}

