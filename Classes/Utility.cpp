#include "Utility.h"
#include "math.h"

int Utility::getNumberDigit(int num)
{
	return static_cast<int>(log10(static_cast<float>(num))) + 1;
}

cocos2d::Vec2 Utility::rotateVec2(cocos2d::Vec2& vector_vec2, float degree, bool clockwise)
{
	float radian = degree / 180 * M_PI;
	return cocos2d::Vec2(vector_vec2.y*sin(radian) - vector_vec2.x*cos(radian), vector_vec2.x*sin(radian) + vector_vec2.y*cos(radian));
}