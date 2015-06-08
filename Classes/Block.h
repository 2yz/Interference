#ifndef BLOCK_H_
#define BLOCK_H_

#include "BaseObject.h"
#include "cocos2d.h"

class Block : public BaseObject
{
public:
	CREATE_FUNC(Block);
	Block();
    static cocos2d::Sprite* createBlock(const char* name, float PositionX, float PositionY);
	virtual bool init() override;
    
};

#endif /* BLOCK_H_ */