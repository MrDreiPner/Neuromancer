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
	void setPeriTarget(vector<Perimeter*>& targetList);
	bool attack(Character& target) override;
	Perimeter* getPeriTarget() { return periTarget; };
	int getNum() { return points; };
	string getName() { return name; };

private:
	Perimeter* periTarget;
	string name;
};

