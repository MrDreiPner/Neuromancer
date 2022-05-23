#pragma once
#include "Character.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Perimeter.h"
#include "Server.h"

using namespace std;

class Hacker : public Character
{
public:
	Hacker(int x);
	~Hacker();
	void setTarget(vector<Character*>& targetList) override;
	Character* getTarget() override;
	bool attack(Character& target) override;
	Character* getTarget(int x) { return periTarget; };
	int getNum() { return points; };
	string getName() { return name; };

private:
	Perimeter* periTarget;
	int points;
	string name;
};

