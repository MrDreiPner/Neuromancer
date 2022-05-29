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
	Agent(int x);
	~Agent();
	void setTarget(vector<Character*>& targetList);
	Character* getTarget() override;
	bool attack(Character& target) override;
	Character* getTarget(int x) { return hackTarget; };
	int getNum() { return points; };
	string getName() { return name; };

private:
	string name;
	Hacker* hackTarget;
};

