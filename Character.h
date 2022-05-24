#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <mutex>

using namespace std;

class Character
{
public:
	virtual void setTarget(vector<Character*>& targetList) = 0;
	virtual Character* getTarget() = 0;
	virtual bool  attack(Character& target) = 0;
	virtual string getName() = 0;
	virtual Character* getTarget(int x) { return NULL; };
	virtual int getNum() { return NULL; };
	virtual void setPoints(int x) { points = x; };
	virtual int getPoints() { return points; };
	int getHP() { return hp; };
	void setHP(int x) { hp = x; };
	int getAttVal() { return attVal; };
	void setAttVal(int x) { attVal = x; };
	bool getStatus() { return active; };
	void setStatus(bool x) { active = x; };
	mutex lockChar;

protected:
	Character* target;
	int hp = 0;
	int attVal = 0;
	bool active = true;
	int points = 0;
};

