#pragma once
#include "Character.h"
#include "Perimeter.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Server
{
public:
	Server();
	~Server();
	int getNum() { return numDefZones; };
	int getPoints() { return points; };
	void setPoints(int x) { points = x; };
	int getHP() { return hp; };
	void setHP(int x) { hp = x; };
	bool getStatus() { return active; };
	void setStatus(bool x) { active = x; };
	vector<Perimeter*> getTarget() { return DefZones; };
	string getName() { return name; };
	mutex lockServer;

private:
	int hp;
	int points;
	string name;
	bool active = true;
	int numDefZones = 5;
	vector<Perimeter*> DefZones;
};

