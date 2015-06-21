#ifndef BLOCK_H_
#define BLOCK_H_

#include "BaseObject.h"

class Block : public BaseObject
{
public:
	static Block* create(bool isEdge = false);
	explicit Block(bool isEdge = false);
	virtual bool init() override;
	virtual void initMessage() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
	virtual void onContact(Message& message) override;
protected:
	bool _isEdge;
	int score_;
};

#endif /* BLOCK_H_ */