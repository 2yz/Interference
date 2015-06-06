#ifndef BOSS_H_
#define BOSS_H_

#include "BasePlane.h"

class Boss : public BasePlane
{
public:
	CREATE_FUNC(Boss);
	Boss();
	virtual bool init() override;
};

#endif /* BOSS_H_ */