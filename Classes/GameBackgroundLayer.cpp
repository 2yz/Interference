#include "GameBackgroundLayer.h"
#include "ConfigUtil.h"

USING_NS_CC;

bool GameBackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	background1 = Sprite::create(kBackgroundTexture);
	background1->setPosition(config::kBattleScene / 2);
	this->addChild(background1);
	return true;
}

