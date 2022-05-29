#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

using namespace std;

class Perimeter : public Character
{
public:
	Perimeter(int x);
	virtual ~Perimeter();
	int getDef() { return defense; };
	void setDef(int x) { defense = x; };
	void incrDef() { defense++; };
	void decrDef() { defense--; };
	int getPres() { return pressure; };
	void incrPres() {pressure++; };
	void zeroPres() { pressure = 0; };
	int getID() { return ID; };
	string getName() { return name; };
	int getNameID() { return nameID; };
	void setTarget(vector<Character*>& targetList);
	Character* getTarget() override;
	bool  attack(Character& target) override;

private:
	int defense = 20;
	int pressure = 0;
	int ID;
	int nameID;
	string name = "DefZone";
};

