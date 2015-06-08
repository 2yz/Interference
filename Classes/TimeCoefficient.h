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
	TimeCoefficient* _parent;
	float _timeCoefficient;
};


#endif /* TIMECOEFFICIENT_H_ */