#ifndef BOSS_H_
#define BOSS_H_

#include "BaseEnemy.h"

class Boss : public BaseEnemy
{
public:
	CREATE_FUNC(Boss);
	Boss();
	virtual bool init() override;
};

#endif /* BOSS_H_ */