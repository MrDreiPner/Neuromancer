#include "Arena.h"

using namespace std;

void watchCore(Server* Core, int& counter);
void launchAttack(Hacker& hacker, Server& core, Arena& Arena, int& counter, int& critCounter);
void launchHunt(Character& agent, vector<Character*>& hackTeam, vector<Character*>& core, Arena& Arena);

Arena::Arena() {
	Core = new Server();
	for (int i = 0; i < numHaxxers; i++) {
		hackTeam.push_back(new Hacker(i));
	}
	for (int i = 0; i < numAgents; i++) {
		secTeam.push_back(new Agent(i));
	}
	cout << "\nPress any button to start Neuromancing!" << endl;
	char dummy = _getch();
}

Arena::~Arena() {
	delete(Core);
	for (int i = 0; i < numHaxxers; i++) {
		delete(hackTeam[i]);
	}
	for (int i = 0; i < numAgents; i++) {
		delete(secTeam[i]);
	}
	//cout <<"Arena destructed. Game Over" << endl;
}

void Arena::startBreach() {
	system("cls");
	srand(time(NULL));
	auto startNeuroTimer = chrono::steady_clock::now();
	int x = 0;
	int counter = 0;
	int critCounter = 0;
	thread CoreWatch(watchCore, ref(Core), ref(counter));
	thread Haxxor1(launchAttack, ref(*hackTeam[x]), ref(*Core), ref(*this), ref(counter), ref(critCounter)); x++;
	thread Haxxor2(launchAttack, ref(*hackTeam[x]), ref(*Core), ref(*this), ref(counter), ref(critCounter)); x++;
	thread Haxxor3(launchAttack, ref(*hackTeam[x]), ref(*Core), ref(*this), ref(counter), ref(critCounter)); x++;
	thread Haxxor4(launchAttack, ref(*hackTeam[x]), ref(*Core), ref(*this), ref(counter), ref(critCounter)); x++;
	thread Haxxor5(launchAttack, ref(*hackTeam[x]), ref(*Core), ref(*this), ref(counter), ref(critCounter)); x = 0;
	//thread Agent1(launchHunt, ref(*secTeam[x]), ref(hackTeam), ref(Core), ref(*this)); x++;
	//thread Agent2(launchHunt, ref(*secTeam[x]), ref(hackTeam), ref(Core), ref(*this)); 
	CoreWatch.join();
	Haxxor1.join();
	Haxxor2.join();
	Haxxor3.join();
	Haxxor4.join();
	Haxxor5.join();
	//Agent1.join();
	//Agent2.join();

	int sum = 0;
	for (int i = 0; i < numHaxxers; i++) {
		sum += hackTeam[i]->getNum();
	}
	int hpSum = 500;
	cout << "\nServer HP = " << Core->getHP() << endl;
	cout << "Collective Hacker points = " << sum << "\n\nHacker Team" << endl;
	for (int i = 0; i < numHaxxers; i++) {
		cout << hackTeam[i]->getName() << " made " << hackTeam[i]->getNum() << " points" << endl; 
		cout << "HP left = " << hackTeam[i]->getHP() << endl;
		hpSum -= 100 - hackTeam[i]->getHP();
	}
	cout << "Number of Critical fails = " << critCounter << " dealing a cumulative " << critCounter * 5 << " HP damage" << endl;
	hpSum += critCounter * 5;
	cout << endl << "Server Defense" << endl;
	cout << Core->getName() << " made " << Core->getPoints() << " points" << endl;
	hpSum += Core->getPoints();
	cout << endl << "Security Team" << endl;
	for (int i = 0; i < numAgents; i++) {
		cout << secTeam[i]->getName() << " made " << secTeam[i]->getNum() << " points" << endl;
		hpSum += secTeam[i]->getNum();
	}
	cout << "\nHP check should be 500 - is -> " << hpSum << endl;
	auto endTimer = chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startNeuroTimer).count();
	cout << "\nRuntime - Neuromancer: " << elapsed << " ms" << endl;

}

void watchCore(Server* Core, int& counter) {
	while (counter != 5) {
		//keep looping
	}
	Core->lockServer.lock();
	Core->setStatus(false);
	Core->lockServer.unlock();
}

void launchAttack(Hacker& hacker, Server& core, Arena& Arena, int& counter, int& critCounter) {
	random_device generator;
	while (hacker.getStatus() && core.getStatus()) {
		hacker.lockChar.lock();
		vector<Perimeter*> DefZones = core.getTarget();
		hacker.setPeriTarget(DefZones);
		hacker.lockChar.unlock();
		if (generator() % 100 == 0) {
			hacker.lockChar.lock();
			hacker.setHP(hacker.getHP() - 5);
			hacker.lockChar.unlock();
			Arena.lockArena.lock();
			critCounter++;
			cout << hacker.getName() << " failed critically!" << endl;
			cout << "Hacker HP = " << hacker.getHP() << " | Attack Value = " << hacker.getAttVal() << endl;
			Arena.lockArena.unlock();
		}
		else {
			bool success = hacker.attack(*hacker.getPeriTarget());
			Character* currTarg = hacker.getTarget(0);
			Perimeter* perTarg = (Perimeter*)currTarg;
			/*hacker.lockChar.lock();
			int hackerAtt = hacker.getAttVal();
			string hackerName = hacker.getName();
			hacker.lockChar.unlock();
			Arena.lockArena.lock();
			if (success) {
				cout << hackerName << " succesful attack on " << perTarg->getName() << " " << perTarg->getNameID() << endl;
				cout << perTarg->getName() << " " << perTarg->getNameID() << " new Defense Value = " << perTarg->getDef() << endl;
			}
			else {
				cout << hacker.getName() << " failed attack on " << perTarg->getName() << " " << perTarg->getNameID()<< " | New pressure = "<< perTarg->getPres() << endl;
				cout << "Hacker HP = " << hackerHP << " | Attack Value = "<< hackerAtt << endl;
			}
			Arena.lockArena.unlock();*/
		}
		int hackerHP = hacker.getHP();
		if ((hackerHP % 10 == 0) && hackerHP != 100) {
			hacker.lockChar.lock();
			hacker.setAttVal(hacker.getAttVal() - 2);
			hacker.lockChar.unlock();
		}
		if (hackerHP <= 0) {
			hacker.lockChar.lock();
			hacker.setStatus(false);
			hacker.lockChar.unlock();
		}
		if (hackerHP <= 0) {
			Arena.lockArena.lock();
			cout << hacker.getName() << " has been terminated! " << hacker.getNum() << " points collected" << endl;
			Arena.lockArena.unlock();
		}
	}
	Arena.lockArena.lock();
	counter++;
	Arena.lockArena.unlock();
}

void launchHunt(Character& agent, vector<Character*>& hackTeam, vector<Character*>& core, Arena& Arena) {
	random_device generator;
	while (core[0]->getStatus()) {
		agent.setTarget(hackTeam);
		Hacker* hackerTarget = (Hacker*)agent.getTarget();
		if (generator() % 100 < 20) {
			hackerTarget->lockChar.lock();
			if (hackerTarget->getHP() > 0) {
				bool killCheck = false;
				killCheck = agent.attack(*hackerTarget);
				if (killCheck) {
					Arena.lockArena.lock();
					cout << agent.getName() << " eliminated " << hackerTarget->getName() << " | Points: "<< agent.getNum() << endl;
					Arena.lockArena.unlock();
				}
			}
			hackerTarget->lockChar.unlock();
		}
	}
}

