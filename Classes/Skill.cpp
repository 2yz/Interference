#include "Skill.h"

Skill::Skill() : _timer(0.0f), _CD(false)
{
}

Skill::~Skill()
{
}

bool Skill::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

bool Skill::run(const cocos2d::Vec2& velocity, cocos2d::Node* parent, cocos2d::Node* target, int bulletParent)
{
	if (_CD)
		return false;
	_CD = true;
	return true;
}


SkillCategory Skill::getSkillCategory()
{
	return _skillCategory;
}

void Skill::update(float deltaTime)
{
	Node::update(deltaTime);
	if (_CD)
	{
		_timer += deltaTime;
		if (_timer >= _CDTime)
		{
			_CD = false;
			_timer = 0.0f;
		}
	}
}