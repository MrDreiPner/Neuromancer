#include "Agent.h"

Agent::Agent(int x) {
	std::string nameArr[] = { "Smith", "Walter" };
	name = nameArr[x];
	std::cout << name << " the Agent has been created!" << std::endl;
}

Agent::~Agent() {
	//std::cout << name << " the Agent has been destroyed!" << std::endl;
}

void Agent::setTarget(std::vector<Character*>& targetList) {
	random_device generator;
	do {
		hackTarget = (Hacker*)targetList[generator() % 5];
	} while (hackTarget->getStatus() != true);
}

Character* Agent::getTarget() {
	return hackTarget;
}

bool Agent::attack(Character& target) {
	
	return 0;
}