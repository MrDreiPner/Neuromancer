#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <thread>
#include <random>
#include <conio.h>
#include "Arena.h"
#include "Character.h"
#include "Hacker.h"
#include "Agent.h"
#include "Server.h"
#include "Perimeter.h"

class Arena
{
public:
	Arena();
	~Arena();
	void startBreach();
	std::vector<Character*>* getHackTeam() { return &hackTeam; };
	std::vector<Character*>* getSecTeam() { return &secTeam; };
	std::vector<Character*>* getCore() { return &Core; };
	mutex lockArena;
private:
	std::vector<Character*> hackTeam;
	std::vector<Character*> secTeam;
	std::vector<Character*> Core;
	int numHaxxers = 5;
	int numAgents = 2;
	int attacksLaunched = 0;
	char teamMode = 0;
};

