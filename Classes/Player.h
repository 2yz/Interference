#ifndef Player_H_
#define Player_H_

#include "BasePlane.h"

class Player : public BasePlane
{
public:
	CREATE_FUNC(Player);
	Player();
	virtual ~Player();
	virtual bool init() override;
	virtual void initMessage() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
	virtual void onContact(Message& message) override;
	float getTraceCoefficient();
	void setTraceCoefficient(float maxSpeed, float acceleration, float delta_time);
	inline void updateMove(float delta_time);
	inline void updateSkillCast(float delta_time);
	virtual void update(float delta_time) override;
protected:
	float acceleration_magnitude_;
private:
	float trace_coefficient_;
};

#endif /* Player_H_ */