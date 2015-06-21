#include "TimeCoefficient.h"

TimeCoefficient::TimeCoefficient() : parent_(nullptr), time_coefficient_(1.0f)
{
}

void TimeCoefficient::setTimeParent(TimeCoefficient* parent)
{
	parent_ = parent;
}

void TimeCoefficient::setTimeCoefficient(float timeCoefficient)
{
	time_coefficient_ = timeCoefficient;
}

float TimeCoefficient::getTimeCoefficient()
{
	if (parent_ != nullptr)
		return time_coefficient_ * parent_->getTimeCoefficient();
	return time_coefficient_;
}