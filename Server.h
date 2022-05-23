#pragma once
#include "Character.h"
#include "Perimeter.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Server : public Character
{
public:
	Server(int x);
	~Server();
	void setTarget(vector<Character*>& targetList) override;
	Character* getTarget() override;
	bool attack(Character& target) override;
	int getNum() { return numDefZones; };
	Character* getTarget(int x) { return DefZones[x]; };
	string getName() { return name; };

private:
	string name;
	int numDefZones = 5;
	vector<Character*> DefZones;
};

