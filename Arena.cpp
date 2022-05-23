#include "Arena.h"

using namespace std;

void watchCore(vector<Character*> Core, int& counter);
void launchAttack(Character& hacker, vector<Character*>& core, Arena& Arena, int& counter);
void launchHunt(Character& agent, vector<Character*>& hackTeam, vector<Character*>& core, Arena& Arena);

Arena::Arena() {
	Core.push_back(new Server(0));
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
	delete(Core[0]);
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
	thread CoreWatch(watchCore, ref(Core), ref(counter));
	thread Haxxor1(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter)); x++;
	thread Haxxor2(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter)); x++;
	thread Haxxor3(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter)); x++;
	thread Haxxor4(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter)); x++;
	thread Haxxor5(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter)); x = 0;
	thread Agent1(launchHunt, ref(*secTeam[x]), ref(hackTeam), ref(Core), ref(*this)); x++;
	thread Agent2(launchHunt, ref(*secTeam[x]), ref(hackTeam), ref(Core), ref(*this)); 
	CoreWatch.join();
	Haxxor1.join();
	Haxxor2.join();
	Haxxor3.join();
	Haxxor4.join();
	Haxxor5.join();
	Agent1.join();
	Agent2.join();

	int sum = 0;
	for (int i = 0; i < numHaxxers; i++) {
		sum += hackTeam[i]->getNum();
	}

	cout << "\nServer HP = " << Core[0]->getHP() << endl;
	cout << "Collective points = " << sum << "\n\nHacker Team" << endl;
	for (int i = 0; i < numHaxxers; i++) {
		cout << hackTeam[i]->getName() << " made " << hackTeam[i]->getNum() << " points" << endl; 
		cout << "HP left = " << hackTeam[i]->getHP() << endl;
	}
	cout << endl << "Security Team" << endl;
	for (int i = 0; i < numAgents; i++) {
		cout << secTeam[i]->getName() << " made " << secTeam[i]->getNum() << " points" << endl;
	}
	cout << endl;
	auto endTimer = chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startNeuroTimer).count();
	cout << "Runtime - Neuromancer: " << elapsed << " ms" << endl;

}

void watchCore(vector<Character*> Core, int& counter) {
	while (counter != 5) {
		//keep looping
	}
	Core[0]->lockChar.lock();
	Core[0]->setStatus(false);
	Core[0]->lockChar.unlock();
}

void launchAttack(Character& hacker, vector<Character*>& core, Arena& Arena, int& counter) {
	//random_device generator;
	while (hacker.getStatus() && core[0]->getStatus()) {
		hacker.lockChar.lock();
		hacker.setTarget(core);
		hacker.lockChar.unlock();
		if (rand() % 100 == 0) {
			hacker.lockChar.lock();
			hacker.setHP(hacker.getHP() - 5);
			hacker.lockChar.unlock();
			Arena.lockArena.lock();
			cout << hacker.getName() << " failed critically!" << endl;
			cout << "Hacker HP = " << hacker.getHP() << " | Attack Value = " << hacker.getAttVal() << endl;
			Arena.lockArena.unlock();
		}
		else {
			bool success = hacker.attack(*core[0]);
			Character* currTarg = hacker.getTarget(0);
			Perimeter* perTarg = (Perimeter*)currTarg;
			/*Arena.lockArena.lock();
			hacker.lockChar.lock();
			if (success) {
				cout << hacker.getName() << " succesful attack on " << perTarg->getName() << " " << perTarg->getNameID() << endl;
				cout << perTarg->getName() << " " << perTarg->getNameID() << " new Defense Value = " << perTarg->getDef() << endl;
			}
			else {
				cout << hacker.getName() << " failed attack on " << perTarg->getName() << " " << perTarg->getNameID()<< " | New pressure = "<< perTarg->getPres() << endl;
				cout << "Hacker HP = " << hacker.getHP() << " | Attack Value = "<< hacker.getAttVal() << endl;
			}
			hacker.lockChar.unlock();
			Arena.lockArena.unlock();*/
		}
		hacker.lockChar.lock();
		if ((hacker.getHP() % 10 == 0) && hacker.getHP() != 100) {
			hacker.setAttVal(hacker.getAttVal() - 2);
		}
		if (hacker.getHP() <= 0) {
			hacker.setStatus(false);
		}
		if (hacker.getHP() <= 0) {
			Arena.lockArena.lock();
			cout << hacker.getName() << " has been terminated! " << hacker.getNum() << " points collected" << endl;
			Arena.lockArena.unlock();
		}

		hacker.lockChar.unlock();
	}
	Arena.lockArena.lock();
	counter++;
	Arena.lockArena.unlock();
}

void launchHunt(Character& agent, vector<Character*>& hackTeam, vector<Character*>& core, Arena& Arena) {
	//random_device generator;
	while (core[0]->getStatus()) {
		agent.setTarget(hackTeam);
		Hacker* hackerTarget = (Hacker*)agent.getTarget();
		if (rand() % 100 < 5) {
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

