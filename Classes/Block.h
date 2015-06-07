#ifndef BLOCK_H_
#define BLOCK_H_

#include "BaseObject.h"

class Block : public BaseObject
{
public:
	CREATE_FUNC(Block);
	Block();
	virtual bool init() override;
};

#endif /* BLOCK_H_ */