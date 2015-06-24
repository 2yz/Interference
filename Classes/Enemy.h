#ifndef ENEMY_H_
#define ENEMY_H_

#include "BaseEnemy.h"

enum class EnemyState : unsigned int
{
	NA,

};

class Enemy : public BaseEnemy
{
public:
	CREATE_FUNC(Enemy);
	Enemy();
	virtual bool init() override;
	virtual void initMessage() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
	void onContact(Message& message) override;
	virtual void update(float delta_time) override;
	void updateStateMachine(float delta_time);
	void setState(EnemyState battle_state);
	void enterState(EnemyState battle_state);
	void exitState();
};

#endif /* ENEMY_H_ */