#include "LoadScene.h"
#include "ConfigUtil.h"
#include "BattleScene.h"
#include <thread>

USING_NS_CC;

LoadScene::LoadScene() : load_state_(LoadState::NA), animation_state_(AnimationState::NA), loaded_num_(0), total_num_(0), logo_(nullptr)
{
}

bool LoadScene::init()
{
	if (!Scene::init())
		return false;
	Director::getInstance()->getTextureCache()->addImage(ALF_LOGO_TEXTURE);
	logo_ = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(ALF_LOGO_TEXTURE));
	logo_->setPosition(config::visible_size / 2);
	logo_->setOpacity(0.0f);
	this->addChild(logo_);
	animation_state_ = AnimationState::FADE_IN;
	logo_->runAction(Sequence::create(DelayTime::create(0.4f), FadeIn::create(1.0f), DelayTime::create(0.2f), CallFuncN::create([&](Node* sender){ animation_state_ = AnimationState::WAIT_LOADING; }), nullptr));
	scheduleUpdate();
	return true;
}

void LoadScene::onEnter()
{
	Scene::onEnter();
	texture_vector_.push_back(BIRTH_TEXTURE);
	texture_vector_.push_back(DEATH_TEXTURE);
	texture_vector_.push_back(BOOM_TEXTURE);
	texture_vector_.push_back(BACKGROUND_TEXTURE);
	texture_vector_.push_back(MENU_BACKGROUND_TEXTURE);
	texture_vector_.push_back(BUTTON_NORMAL_TEXTURE);
	texture_vector_.push_back(BUTTON_PRESS_TEXTURE);
	texture_vector_.push_back("texture/background1.png");
	texture_vector_.push_back("texture/background2.png");
	texture_vector_.push_back("texture/background3.png");
	total_num_ = 1 + texture_vector_.size();
	load_state_ = LoadState::LOADING;
	for (auto texture_name : texture_vector_)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(texture_name, [&](cocos2d::Texture2D* texture)
		{
			loaded_num_ += 1;
		});
	}
	Director::getInstance()->getTextureCache()->addImageAsync(MAIN_TEXTURE_PNG, [&](cocos2d::Texture2D* texture)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MAIN_TEXTURE_PLIST, texture);
		loaded_num_ += 1;
	});
}

void LoadScene::update(float delta_time)
{
	if (load_state_ == LoadState::LOADING && loaded_num_ == total_num_)
		load_state_ = LoadState::LOADED;
	if (load_state_ == LoadState::LOADED && animation_state_ == AnimationState::WAIT_LOADING)
	{
		animation_state_ = AnimationState::FADE_OUT;
		logo_->runAction(Sequence::create(FadeOut::create(1.0f), CallFuncN::create([&](Node* sender)
		{
			Director::getInstance()->replaceScene(BattleScene::create());
		}), nullptr));
	}
}