#include "Controller.h"

bool Controller::moveUp = false;
bool Controller::moveDown = false;
bool Controller::moveLeft = false;
bool Controller::moveRight = false;

bool Controller::getMoveUp()
{
	return moveUp;
}

bool Controller::getMoveDown()
{
	return moveDown;
}

bool Controller::getMoveLeft()
{
	return moveLeft;
}

bool Controller::getMoveRight()
{
	return moveRight;
}

void Controller::setMoveUp(bool value)
{
	moveUp = value;
}

void Controller::setMoveDown(bool value)
{
	moveDown = value;
}

void Controller::setMoveLeft(bool value)
{
	moveLeft = value;
}

void Controller::setMoveRight(bool value)
{
	moveRight = value;
}