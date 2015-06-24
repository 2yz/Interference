#ifndef PLAYERDATA_H_
#define PLAYERDATA_H_

class PlayerUserData {
public:
	PlayerUserData(float hp, float hp_max);
	float getHP();
	void setHP(float hp);
	float getMaxHP();
	void setMaxHP(float hp_max);
	bool isAlive();
protected:
	float hp_;
	float hp_max_;
};


#endif /* PLAYERDATA_H_ */