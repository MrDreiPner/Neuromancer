#pragma once
#include "Character.h"
#include <iostream>
#include <vector>
#include <string>
#include "Hacker.h"

using namespace std;

class Agent : public Character
{
public:
	Agent(int x, int tactic);
	~Agent();
	void setTarget(vector<Character*>& targetList) override;
	Character* getTarget() override;
	bool attack(Character& target) override;
	Character* getTarget(int x) { return hackTarget; };
	int getNum() { return points; };
	string getName() { return name; };

private:
	string name;
	Hacker* hackTarget;
};

