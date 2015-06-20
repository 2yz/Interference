#include "LogoScene.h"
#include "ConfigUtil.h"
#include "BattleScene.h"
#include <thread>

USING_NS_CC;

LogoScene::LogoScene() : animation_finish_(false), load_finish_(false), loaded_num_(0), total_num_(0)
{
}

bool LogoScene::init()
{
	if (!Scene::init())
		return false;
	Director::getInstance()->getTextureCache()->addImage(ALF_LOGO_TEXTURE);
	auto logo = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(ALF_LOGO_TEXTURE));
	logo->setPosition(config::visible_size / 2);
	this->addChild(logo);
	logo->setOpacity(0.0f);
	logo->runAction(Sequence::create(FadeIn::create(1.0f),MoveBy::create(1.0f,Vec2::ZERO), FadeOut::create(1.0f), CallFuncN::create([&](Node* sender){ animation_finish_ = true; startBattle(); }), nullptr));
	return true;
}

void LogoScene::onEnter()
{
	Scene::onEnter();
	total_num_ = 9;
	Director::getInstance()->getTextureCache()->addImageAsync(MAIN_TEXTURE_PNG, CC_CALLBACK_1(LogoScene::spriteFrameCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(kBirthTexture, CC_CALLBACK_1(LogoScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(kDeathTexture, CC_CALLBACK_1(LogoScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(kBoomTexture, CC_CALLBACK_1(LogoScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(BACKGROUND_TEXTURE, CC_CALLBACK_1(LogoScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(MENU_BACKGROUND_TEXTURE, CC_CALLBACK_1(LogoScene::loadingCallBack, this));
	std::string background_texture[3] = { "texture/background1.png", "texture/background2.png", "texture/background3.png" };
	for (int i = 0; i < 3; ++i)
		Director::getInstance()->getTextureCache()->addImageAsync(background_texture[i], CC_CALLBACK_1(LogoScene::loadingCallBack, this));
	load_finish_ = true;
}

void LogoScene::spriteFrameCallBack(cocos2d::Texture2D* texture)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MAIN_TEXTURE_PLIST,texture);
	loadingCallBack(texture);
}

void LogoScene::loadingCallBack(cocos2d::Texture2D* texture)
{
	loaded_num_ += 1;
	if (loaded_num_ = total_num_)
	{
		load_finish_ = true;
		startBattle();
	}
}

void LogoScene::startBattle()
{
	if (animation_finish_&&load_finish_)
	{
		auto battle_scene = BattleScene::create();
		Director::getInstance()->replaceScene(battle_scene);
	}
}
