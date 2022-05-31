#include "Hacker.h"

Hacker::Hacker(int x, int tactic, vector<Character*>& Core) {
	std::string nameArr[] = { "HackerMan", "HackerWoman", "xXx_HaxxLord_xXx", "OwO_Snuggle", "MasterH8r_xD"};
	name = nameArr[x];
	hp = 100;
	attVal = 20;
	points = 0;
	bool validInput = false;
	char input = 0;
	//Tactics get decided selected
	if (tactic == 2) {
		while (validInput == false) {
			cout << "What strategy does " << name << " employ?\n(r) Random pattern\n(v) Vulnerarbility targeting" << endl;
			cin >> input;
			if (input == 'r' || input == 'v') {
				if (input == 'v')
					tactic = 3;
				validInput = true;
			}
			else
				cin.clear();
		}
	}
	else {
		if (x == 0) {
			isLeader = true;
			tactic = 3;
			//hp = 1;
			setTarget(Core);
			cout << name << " is the Leader!" << endl;
		}
	}
	strategy = tactic;
	std::cout << name << " the Hacker has been created!" << std::endl;
}

Hacker::~Hacker() {
	//std::cout << name << " the Hacker has been destroyed!" << std::endl;
}

void Hacker::setTarget(std::vector<Character*>& targetList) {
	if (strategy == 3) {
		Perimeter* periList[5];
		//targetList[0]->lockChar.lock();
		for (int i = 0; i < 5; i++) {
			periList[i] = (Perimeter*)targetList[0]->getTarget(i);
			periList[i]->lockChar.lock();
			if (i == 0)
				periTarget = periList[i];
			else if (periTarget->getDef() > periList[i]->getDef())
				periTarget = periList[i];
			periList[i]->lockChar.unlock();
		}
		//targetList[0]->lockChar.unlock();
	}
	else if (strategy == 2 || isLeader == true) {
		random_device generator;
		periTarget = (Perimeter*)targetList[0]->getTarget(generator() % 5);
		
	}
	//else if(leader->getLeaderStatus())
	//	periTarget = (Perimeter*)leader->getTarget();
	//cout << "Defzone " << periTarget->getName() << " targeted by " << this->getName() << endl;
}

Character* Hacker::getTarget() {
	return periTarget;
}

void Hacker::checkLeader(vector<Character*>& hackTeam) {
	if (strategy == 1 && isLeader == false) {
		int leaderCount = 0;
		for (int i = 0; i < 5; i++) {
			//if(hackTeam[i] != this)
			hackTeam[i]->lockChar.lock();
			//cout << hackTeam[i]->getName() << " is locked" << endl;
		}
		for (int i = 0; i < 5; i++) {
			if (hackTeam[i]->getLeaderStatus() == true) {
				leaderCount++;
				leaderStatus = true;
				periTarget = (Perimeter*)hackTeam[i]->getTarget();
				//cout << hackTeam[i]->getName() << " is the leader of " << name << " | PeriTarget is Perimeter " << periTarget->getNameID() << endl;
				//assert(!leaderCount > 1, "Too many leaders");
			}
		}
		if (leaderCount < 1) {
			isLeader = true;
			strategy = 3;
			//cout << "\n" << name << " is new Leader!" << endl;
		}

		for (int i = 4; i >= 0; i--) {
			//cout << hackTeam[i]->getName() << " is unlocked" << endl;
			//if (hackTeam[i] != this)
			hackTeam[i]->lockChar.unlock();
		}
	}
}

bool Hacker::attack(Character& target) {
	periTarget->lockChar.lock();
	int pressure = periTarget->getPres();
	int defVal = periTarget->getDef();
	periTarget->lockChar.unlock();
	//hacker succeded in breaching perimeter
	if (attVal + pressure > defVal) {
		//Server gets locked and manipulated
		target.lockChar.lock();
		//checking if server is even active (above 0 hp)
		if (target.getStatus() == true) {
			target.setHP(target.getHP() - 1);
		}
		else {
			target.lockChar.unlock();
			return false;
		}
		//if Server gets set to 0 hp, it´s status is changed to inactive - killing it
		if (target.getHP() <= 0) {
			target.setStatus(false);
		}
		target.lockChar.unlock();
		int diff = attVal + pressure - defVal;
		//Perimeter Pressure gets reset, defense increased
		periTarget->lockChar.lock();
		periTarget->zeroPres();
		periTarget->setDef(periTarget->getDef() + 4);
		periTarget->lockChar.unlock();
		//hacker gets points and an increase to attack
		points++;
		attVal++;
		//Perimeter defense gets restocked from other perimeters (in a rotation)
		while (diff > 0) {
			for (int i = 0; i < target.getNum(); i++) {
				if (diff > 0) {
					target.lockChar.lock();
					Perimeter* diffPeri = (Perimeter*)target.getTarget(i);
					if (i != periTarget->getID() && diffPeri->getDef() > 0) {
						periTarget->lockChar.lock();
						diffPeri->lockChar.lock();
						diffPeri->decrDef();
						periTarget->incrDef();
						diffPeri->lockChar.unlock();
						periTarget->lockChar.unlock();
						diff--;
					}
					target.lockChar.unlock();
				}
			}
		}
		return true;
	}
	//Hacker failed to breach perimeter
	else {
		target.lockChar.lock();
		lockChar.lock();
		if (hp > 0) {
			hp--;
			target.setPoints(target.getPoints() + 1);
		}
		lockChar.unlock();
		target.lockChar.unlock();
		periTarget->lockChar.lock();
		periTarget->incrPres();
		periTarget->lockChar.unlock();
		return false;
	}
}