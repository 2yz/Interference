#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller
{
public:
	static bool getMoveUp();
	static bool getMoveDown();
	static bool getMoveLeft();
	static bool getMoveRight();
	static void setMoveUp(bool value);
	static void setMoveDown(bool value);
	static void setMoveLeft(bool value);
	static void setMoveRight(bool value);
private:
	static bool moveUp;
	static bool moveDown;
	static bool moveLeft;
	static bool moveRight;
};

#endif /* CONTROLLER_H_ */