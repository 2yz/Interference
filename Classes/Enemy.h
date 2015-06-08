#ifndef ENEMY_H_
#define ENEMY_H_

#include "BaseEnemy.h"

class Enemy : public BaseEnemy
{
public:
	CREATE_FUNC(Enemy);
	Enemy();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
protected:
	virtual void update(float deltaTime) override;
};

#endif /* ENEMY_H_ */