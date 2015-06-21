#ifndef SIMPLEBATTLE_H_
#define SIMPLEBATTLE_H_

#include "BattleLayer.h"

class SimpleBattle : public BattleLayer
{
public:
	CREATE_FUNC(SimpleBattle);
	virtual void updateStateMachine(float delta_time) override;
	virtual void setState(BattleState battle_state) override;
	virtual void enterState(BattleState battle_state) override;
	virtual void exitState(BattleState battle_state) override;
};

#endif /* SIMPLEBATTLE_H_ */