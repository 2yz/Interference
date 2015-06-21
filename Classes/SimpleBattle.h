#ifndef SIMPLEBATTLE_H_
#define SIMPLEBATTLE_H_

#include "BattleLayer.h"

class SimpleBattle : public BattleLayer
{
public:
	CREATE_FUNC(SimpleBattle);
	virtual void updateStateMachine(float deltaTime);
	virtual void setState(BattleState battle_state);
	virtual void enterState(BattleState battle_state);
	virtual void exitState(BattleState battle_state);
};

#endif /* SIMPLEBATTLE_H_ */