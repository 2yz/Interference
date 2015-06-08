#include "TimeCoefficient.h"

TimeCoefficient::TimeCoefficient() : _parent(nullptr), _timeCoefficient(1.0f)
{
}

void TimeCoefficient::setTimeParent(TimeCoefficient* parent)
{
	_parent = parent;
}

void TimeCoefficient::setTimeCoefficient(float timeCoefficient)
{
	_timeCoefficient = timeCoefficient;
}

float TimeCoefficient::getTimeCoefficient()
{
	if (_parent != nullptr)
		return _timeCoefficient * _parent->getTimeCoefficient();
	return _timeCoefficient;
}