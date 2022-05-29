#include "Hacker.h"

Hacker::Hacker(int x) {
	std::string nameArr[] = { "HackerMan", "HackerWoman", "xXx_HaxxLord_xXx", "OwO_Snuggle", "MasterH8r_xD"};
	name = nameArr[x];
	hp = 100;
	attVal = 20;
	points = 0;
	std::cout << name << " the Hacker has been created!" << std::endl;
}

Hacker::~Hacker() {
	//std::cout << name << " the Hacker has been destroyed!" << std::endl;
}

void Hacker::setPeriTarget(std::vector<Perimeter*>& targetList) {
	random_device generator;
	periTarget = targetList[generator() % 5];
	//cout << "Defzone " << periTarget->getName() << " targeted by " << this->getName() << endl;
}

Perimeter* Hacker::getPeriTarget() {
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
		periTarget->setDef(periTarget->getDef() + 3);
		periTarget->lockChar.unlock();
		points++;
		attVal++;
		while (diff > 0) {
			target.lockChar.lock();
			for (int i = 0; i < target.getNum(); i++) {
				if (diff > 0) {
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
		target.lockChar.lock();
		target.setPoints(target.getPoints() + 1);
		target.lockChar.unlock();
		periTarget->lockChar.lock();
		periTarget->incrPres();
		periTarget->lockChar.unlock();
		return false;
	}
}