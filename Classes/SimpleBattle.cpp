#include "SimpleBattle.h"
#include "Enemy.h"
#include "AppDelegate.h"
#include "Utility.h"

USING_NS_CC;

void SimpleBattle::updateStateMachine(float delta_time)
{
	switch (battle_state_)
	{
	case BEGIN:
		state_timer_ += delta_time;
		if (state_timer_ > 5.0f)
		{
			int num = random(5, 15);
			for (int i = 0; i < num; ++i)
			{
				auto enemy = Enemy::create();
				enemy->setPosition(Vec2(random(120.0f, config::kEdgeSize.width - 120.0f), random(120.0f, config::kEdgeSize.height - 120.0f)));
				enemy->setVelocity(Vec2(random(0.0f, 160.0f), random(0.0f, 160.0f)));
				this->addChild(enemy);
			}
			state_timer_ -= 5.0f;
			state_count_ += 1;
		}
		if (state_count_ >= 5)
			setState(ROUND1);
		break;
	case ROUND1:
		state_timer_ += delta_time;
		if (state_timer_ > 5.0f)
		{
			Vec2 vector_vec2(1.0f, 0.0f);
			Vec2 position;
			if (player_ != nullptr)
				position = player_->getPosition();
			else
				position = Vec2(config::kBattleScene / 2);
			position += Vec2((rand_minus1_1() > 0 ? 1 : -1)*random(80.0f, 480.0f), (rand_minus1_1() > 0 ? 1 : -1)*random(80.0f, 480.0f));
			if (position.x < 120.0f) position.x = 120.0f;
			else if (position.x > config::kEdgeSize.width - 120.0f) position.x = config::kEdgeSize.width - 120.0f;
			if (position.y < 120.0f) position.y = 120.0f;
			else if (position.y > config::kEdgeSize.height - 120.0f) position.y = config::kEdgeSize.height - 120.0f;
			float speed = random(20.0f, 140.0f);
			for (int i = 0; i < 8; ++i)
			{
				auto enemy = Enemy::create();
				Vec2 direction = Utility::rotateVec2(vector_vec2, i*45.0f);
				enemy->setPosition(position + direction*30.0f);
				enemy->setVelocity(direction*speed);
				this->addChild(enemy);
			}
			state_timer_ -= 10.0f;
			state_count_ += 1;
		}
		if (state_count_ >= 5)
			setState(END);
		break;
	case END:
		if (enemy_.size() == 0)
		{
			sendBattleEvent(BATTLE_EVENT_WIN);
			setState(WIN);
		}
		break;
	case LOSS:
		if (state_count_ == 0)
		{
			sendDestroyEvent();
			state_count_ += 1;
		}
		break;
	default: break;
	}
}

void SimpleBattle::setState(BattleState battle_state)
{
	if (battle_state_ == battle_state)
		return;
	exitState(battle_state_);
	enterState(battle_state);
}

void SimpleBattle::enterState(BattleState battle_state)
{
	battle_state_ = battle_state;
	state_timer_ = 0.0f;
	state_count_ = 0;
	switch (battle_state)
	{
	case BEGIN:
		if (!player_)
		{
			auto player = Player::create();
			player->setPosition(config::kBattleScene / 2);
			auto fadeIn = FadeIn::create(1.0f);
			player->runAction(fadeIn);
			this->addChild(player);

			int block_num = random(10, 25);
			for (int i = 0; i < block_num; ++i)
			{
				auto block = Block::create();
				block->setPosition(random(120.0f, config::kEdgeSize.width - 120.0f), random(120.0f, config::kEdgeSize.height - 120.0f));
				this->addChild(block);
			}
		}
		break;
	default: break;
	}
}

void SimpleBattle::exitState(BattleState battle_state)
{
	switch (battle_state)
	{
	case BEGIN: break;
	default: break;
	}
}