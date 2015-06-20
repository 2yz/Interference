#include "Utility.h"

int Utility::getNumberDigit(int num)
{
	return static_cast<int>(log10(static_cast<float>(num))) + 1;
}