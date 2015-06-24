#ifndef TIMECOEFFICIENT_H_
#define TIMECOEFFICIENT_H_

class TimeCoefficient
{
public:
	TimeCoefficient();
	void setTimeParent(TimeCoefficient* parent);
	void setTimeCoefficient(float timeCoefficient);
	float getTimeCoefficient();
private:
	TimeCoefficient* parent_;
	float time_coefficient_;
};


#endif /* TIMECOEFFICIENT_H_ */