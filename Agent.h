#pragma once
#include "Character.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Agent : public Character
{
public:
	Agent(int x);
	~Agent();
	void setTarget(vector<Character*>& targetList) override;
	Character* getTarget() override;
	bool attack(Character& target) override;
	int getNum() { return points; };
	string getName() { return name; };

private:
	string name;
	int points;
};

