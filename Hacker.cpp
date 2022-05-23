#include "Hacker.h"

Hacker::Hacker(int x) {
	std::string nameArr[] = { "HackerMan", "HackerWoman", "xXx_HaxxLord_xXx", "OwO_Snuggle", "MasterBaiter_xD"};
	name = nameArr[x];
	hp = 1000;
	attVal = 20;
	points = 0;
	std::cout << name << " the Hacker has been created!" << std::endl;
}

Hacker::~Hacker() {
	//std::cout << name << " the Hacker has been destroyed!" << std::endl;
}

void Hacker::setTarget(std::vector<Character*>& targetList) {
	random_device generator;
	periTarget = (Perimeter*) targetList[0]->getTarget(generator() % 5);
	//cout << "Defzone " << periTarget->getName() << " targeted by " << this->getName() << endl;
}

Character* Hacker::getTarget() {
	return periTarget;
}

bool Hacker::attack(Character& target) {
	periTarget->lockChar.lock();
	int pressure = periTarget->getPres();
	int defVal = periTarget->getDef();
	periTarget->lockChar.unlock();
	if (attVal + pressure > defVal) {
		target.lockChar.lock();
		if (target.getStatus() == true) {
			target.setHP(target.getHP() - 1);
		}
		else {
			target.lockChar.unlock();
			return false;
		}
		if (target.getHP() <= 0) {
			target.setStatus(false);
		}
		target.lockChar.unlock();
		int diff = attVal + pressure - defVal;
		periTarget->lockChar.lock();
		periTarget->zeroPres();
		periTarget->setDef(periTarget->getDef() + 1);
		periTarget->lockChar.unlock();
		points++;
		attVal++;
		attVal++;
		while (diff > 0) {
			target.lockChar.lock();
			for (int i = 0; i < target.getNum(); i++) {
				if (diff > 0) {
					Perimeter* diffPeri = (Perimeter*)target.getTarget(i);
					if (i != periTarget->getID() && diffPeri->getDef() > 0) {
						diffPeri->lockChar.lock();
						diffPeri->decrDef();
						diffPeri->lockChar.unlock();
						periTarget->lockChar.lock();
						periTarget->incrDef();
						periTarget->lockChar.unlock();
						diff--;
					}
				}
			}
			target.lockChar.unlock();
		}
		return true;
	}
	else {
		lockChar.lock();
		hp--;
		lockChar.unlock();
		periTarget->lockChar.lock();
		periTarget->incrPres();
		periTarget->lockChar.unlock();
		return false;
	}
}