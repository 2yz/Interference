#ifndef PLAYERDATA_H_
#define PLAYERDATA_H_

class PlayerUserData {
public:
	PlayerUserData(int initHP);
	bool isAliveUnderAttack(int damage);
	int getHP() const;
private:
	int HP;
};


#endif /* PLAYERDATA_H_ */