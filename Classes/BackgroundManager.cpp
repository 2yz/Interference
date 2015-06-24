#include "BackgroundManager.h"
#include "ConfigUtil.h"
#include "Block.h"

USING_NS_CC;

bool BackgroundManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	if (DYNAMIC_BACKGROUNd)
	{
		std::string background_texture[3] = { "texture/background1.png", "texture/background2.png", "texture/background3.png" };
		for (int i = 0; i < 3; ++i)
		{
			auto background = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(background_texture[i]));
			background->setPosition(config::kBattleScene / 2);
			background->setBlendFunc(BlendFunc::ADDITIVE);
			this->addChild(background);
			auto moveby_x = MoveBy::create(random(7.5f, 15.0f), Vec2((rand_minus1_1() > 0 ? 1 : -1)*random(120.0f, 360.0f), 0));
			auto moveby_y = MoveBy::create(random(7.5f, 15.0f), Vec2(0, (rand_minus1_1() > 0 ? 1 : -1)*random(120.0f, 360.0f)));
			Sequence* sequence;
			switch (random(0, 3))
			{
			case 0:
				sequence = Sequence::create(moveby_x, moveby_y, moveby_x->reverse(), moveby_y->reverse(), nullptr);
				break;
			case 1:
				sequence = Sequence::create(moveby_x, moveby_x->reverse(), moveby_y, moveby_y->reverse(), nullptr);
				break;
			case 2:
				sequence = Sequence::create(moveby_y, moveby_x, moveby_y->reverse(), moveby_x->reverse(), nullptr);
				break;
			case 3:
				sequence = Sequence::create(moveby_y, moveby_y->reverse(), moveby_x, moveby_x->reverse(), nullptr);
				break;
			default:
				sequence = nullptr;
				break;
			}
			if (sequence)
				background->runAction(RepeatForever::create(sequence));
		}
	}
	else
	{
		auto background_ = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(BACKGROUND_TEXTURE));
		background_->setPosition(config::kBattleScene / 2);
		background_->setBlendFunc(BlendFunc::ADDITIVE);
		this->addChild(background_);
	}
	// Create Edge
	auto edgeBlock = Block::create(true);
	edgeBlock->setPosition(config::kBattleScene / 2);
	this->addChild(edgeBlock);
	return true;
}

void BackgroundManager::onEnter()
{
	Layer::onEnter();
	for (auto child : _children)
	{
		child->setOpacity(0.0f);
		child->runAction(FadeIn::create(0.5f));
	}
}
