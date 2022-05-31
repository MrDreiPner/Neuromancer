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
	Hacker(int x, int tactic, vector<Character*>& Core);
	~Hacker();
	void setTarget(vector<Character*>& targetList) override;
	Character* getTarget() override;
	bool attack(Character& target) override;
	Character* getTarget(int x) { return periTarget; };
	int getNum() { return points; };
	string getName() { return name; };
	void checkLeader(vector<Character*>& hackTeam);

private:
	Perimeter* periTarget;
	string name;
};

