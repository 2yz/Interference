#ifndef BLOCK_H_
#define BLOCK_H_

#include "BaseObject.h"

class Block : public BaseObject
{
public:
	static Block* create(bool isEdge = false);
	Block(bool isEdge = false);
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
protected:
	bool _isEdge;
};

#endif /* BLOCK_H_ */