#include "BaseTraced.h"

BaseTraced::BaseTraced() :traceCoefficient(0)
{
}

float BaseTraced::getTraceCoefficient()
{
	return traceCoefficient;
}

void BaseTraced::setTraceCoefficient(float maxSpeed, float acceleration, float deltaTime)
{
	traceCoefficient = 1.0f / (maxSpeed / acceleration + deltaTime);
}