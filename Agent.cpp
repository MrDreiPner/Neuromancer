#include "Agent.h"

Agent::Agent(int x, int tactic) {
	std::string nameArr[] = { "Smith", "Walter" };
	name = nameArr[x];
	strategy = tactic;
	std::cout << name << " the Agent has been created!" << std::endl;
}

Agent::~Agent() {
	//std::cout << name << " the Agent has been destroyed!" << std::endl;
}

void Agent::setTarget(std::vector<Character*>& targetList) {
	random_device generator;
	hackTarget = (Hacker*)targetList[generator() % 5];
}

Character* Agent::getTarget() {
	return hackTarget;
}

bool Agent::attack(Character& target) {
	bool killCheck = false;
	hackTarget->setHP(target.getHP() - 1);
	if (hackTarget->getHP() <= 0) {
		hackTarget->setStatus(false);
		killCheck = true;
	}
	points++;
	return killCheck;
}