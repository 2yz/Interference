#ifndef BASEENEMY_H_
#define BASEENEMY_H_

#include "BasePlane.h"

class BaseEnemy : public BasePlane
{
public:
	BaseEnemy();
	virtual bool init() override;
	void setListener();
	void destroyUpdate(float delta_time);
protected:
	bool be_destroyable_; // Is destroyable when contact
	float destroy_damage_; // Damage to Player when destroy for contact
	int score_;
};

#endif /* BASEENEMY_H_ */