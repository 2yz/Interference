#include "Block.h"

Block::Block()
{
}

bool Block::init()
{
	if (!BaseObject::init())
	{
		return false;
	}
	return true;
}