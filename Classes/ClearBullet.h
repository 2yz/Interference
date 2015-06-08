#ifndef CLEARBULLET_H_
#define CLEARBULLET_H_

#include "BaseObject.h"

class ClearBullet : public BaseObject
{
public:
	CREATE_FUNC(ClearBullet);
	ClearBullet();
	virtual bool init() override;
};

#endif /* CLEARBULLET_H_ */