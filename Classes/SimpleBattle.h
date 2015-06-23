#ifndef SIMPLEBATTLE_H_
#define SIMPLEBATTLE_H_

#include "BattleManager.h"

class SimpleBattle : public BattleManager
{
public:
	CREATE_FUNC(SimpleBattle);
	virtual void updateStateMachine(float delta_time) override;
	virtual void setState(BattleManagerState battle_state) override;
	virtual void enterState(BattleManagerState battle_state) override;
	virtual void exitState() override;
};

#endif /* SIMPLEBATTLE_H_ */