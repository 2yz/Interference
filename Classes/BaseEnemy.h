#ifndef BASEENEMY_H_
#define BASEENEMY_H_

#include "BasePlane.h"

class BaseEnemy : public BasePlane
{
public:
	BaseEnemy();
	virtual bool init() override;
	virtual bool onContact(BaseObject* contactNode) override;
protected:
	bool _beDestroyable; // Is destroyable when contact
	float _destroyDamage; // Damage to Player when destroy for contact
};

#endif /* BASEENEMY_H_ */