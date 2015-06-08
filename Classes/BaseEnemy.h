#ifndef BASEENEMY_H_
#define BASEENEMY_H_

#include "BasePlane.h"

class BaseEnemy : public BasePlane
{
public:
	BaseEnemy();
	virtual bool init() override;
protected:
};

#endif /* BASEENEMY_H_ */