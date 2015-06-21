#ifndef UTILITY_H_
#define UTILITY_H_

#include "cocos2d.h"

class Utility
{
public:
	static int getNumberDigit(int num);
	static cocos2d::Vec2 rotateVec2(cocos2d::Vec2& vector_vec2, float degree, bool clockwise = true);
};

#endif /* UTILITY_H_ */