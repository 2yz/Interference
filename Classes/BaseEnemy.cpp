#include "BaseEnemy.h"
#include "ConfigUtil.h"

USING_NS_CC;

BaseEnemy::BaseEnemy()
{
}

bool BaseEnemy::init()
{
	if (!BasePlane::init())
	{
		return false;
	}
	setListener();
	return true;
}

void BaseEnemy::setListener()
{
	auto player_listener = EventListenerCustom::create(DESTROY_EVENT, [=](EventCustom* event)
	{
		auto buf = static_cast<int*>(event->getUserData());
		if (*buf == DESTROY_EVENT_ALL)
			scheduleOnce(schedule_selector(BaseEnemy::destroyUpdate), random(0.5f, 2.0f));
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(player_listener, this);
}

void BaseEnemy::destroyUpdate(float delta_time)
{
	this->onDestroy();
}