#include "HUDLayer.h"
#include <strstream>
#include "HelloWorldScene.h"
#include "Message.h"
#include "ConfigUtil.h"
#include "Utility.h"
#include "PlayerUserData.h"
#include "SkillUserData.h"

USING_NS_CC;

HUDLayer::HUDLayer() : score_(0), score_num_label_(nullptr)
{
}

bool HUDLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	score_label_ = Label::createWithTTF("SCORE", HELVETICA_NEUE_FONT, 20);
	score_label_->setTextColor(Color4B(180, 240, 255, 255));
	score_label_->setAnchorPoint(Vec2(0.0f, 1.0f));
	score_label_->setPosition(config::visible_origin.x + 60.0f, config::visible_size.height - 30.0f);
	addChild(score_label_);

	score_num_label_ = Label::createWithBMFont(NUMBER_BMFONT, "000000");
	score_num_label_->setScale(0.08f);
	score_num_label_->setAnchorPoint(Vec2(0.0f, 1.0f));
	score_num_label_->setPosition(config::visible_origin.x + 60.0f, config::visible_size.height - 60.0f);
	addChild(score_num_label_);

	Vec2 blood_bar_position(config::visible_size.width / 2, config::visible_size.height - 60.0f);
	blood_bar_ = ProgressTimer::create(Sprite::createWithSpriteFrameName(BLOOD_BAR_SPRITE_FRAME));
	blood_bar_->setType(ProgressTimer::Type::BAR);
	blood_bar_->setBarChangeRate(Vec2(1, 0));
	blood_bar_->setMidpoint(Vec2(0, 0));
	blood_bar_->setPercentage(100.0f);
	blood_bar_->setPosition(blood_bar_position);
	addChild(blood_bar_, 8);
	blood_bar_box_ = Sprite::createWithSpriteFrameName(BLOOD_BAR_BOX_SPRITE_FRAME);
	blood_bar_box_->setPosition(blood_bar_position);
	addChild(blood_bar_box_, 9);

	Vec2 attack_position(config::visible_size.width - 360.0f, config::visible_origin.x + 120.0f);
	attack_sprite_ = ProgressTimer::create(Sprite::createWithSpriteFrameName(ATTACK_SPRITE_FRAME));
	attack_sprite_->setType(ProgressTimer::Type::RADIAL);
	attack_sprite_->setReverseDirection(true);
	attack_sprite_->setPercentage(100.0f);
	attack_sprite_->setPosition(attack_position);
	addChild(attack_sprite_, 11);
	attack_dark_sprite_ = Sprite::createWithSpriteFrameName(ATTACK_DARK_SPRITE_FRAME);
	attack_dark_sprite_->setPosition(attack_position);
	addChild(attack_dark_sprite_, 10);

	setEventListener();

	return true;
}

void HUDLayer::setEventListener()
{
	auto listener = EventListenerCustom::create("TimeEvent", [=](EventCustom* event)
	{
		int* buf = static_cast<int*>(event->getUserData());
		log("TimeEvent %d", *buf);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	auto score_listener = EventListenerCustom::create(SCORE_EVENT, [=](EventCustom* event)
	{
		// Get Score
		int* buf = static_cast<int*>(event->getUserData());
		score_ += *buf;
		// Create and Set Score String
		std::ostringstream ostring;
		if (score_ > SCORE_MAX)
			score_ = SCORE_MAX;
		for (int i = 0; i < SCORE_STRING_DIGIT - Utility::getNumberDigit(score_); ++i)
			ostring << "0";
		ostring << score_;
		if (score_num_label_)
			score_num_label_->setString(ostring.str());
		// Output Log
		log("# Score #\n%d", score_);
		log("Digit: %d", Utility::getNumberDigit(score_));
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(score_listener, this);
	auto player_listener = EventListenerCustom::create(PLAYER_EVENT, [=](EventCustom* event)
	{
		PlayerUserData* player_user_data = static_cast<PlayerUserData*>(event->getUserData());
		auto progress_to = ProgressTo::create(0.2f, player_user_data->getHP() / player_user_data->getMaxHP() * 100.0f);
		blood_bar_->runAction(progress_to);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(player_listener, this);
	auto skill_listener = EventListenerCustom::create(SKILL_EVENT, [=](EventCustom* event)
	{
		SkillUserData* skill_user_data = static_cast<SkillUserData*>(event->getUserData());
		auto progress_from_to = ProgressFromTo::create(skill_user_data->getCDTime(), 0.0f, 100.0f);
		switch(skill_user_data->getSkillCategory())
		{
		case ATTACK:
			attack_sprite_->runAction(progress_from_to);
			break;
		default:
			break;
		}
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(skill_listener, this);
}

void HUDLayer::addScoreBy(int addScore)
{
	score_ += addScore;
	updateScore();
}

int HUDLayer::getScore()
{
	return score_;
}

void HUDLayer::updateScore()
{
	std::string strScore;
	std::strstream ss;
	ss << this->score_;
	ss >> strScore;
	score_num_label_->setString(strScore.c_str());
}

void HUDLayer::update(float delta_time)
{

}