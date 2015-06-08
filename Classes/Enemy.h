#ifndef ENEMY_H_
#define ENEMY_H_

#include "BasePlane.h"

class Enemy : public BasePlane
{
public:
	CREATE_FUNC(Enemy);
	Enemy();
	virtual bool init() override;
};

#endif /* ENEMY_H_ */