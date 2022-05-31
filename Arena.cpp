#include "Arena.h"

using namespace std;

void watchCore(vector<Character*> Core, int& counter);
void launchAttack(Character& hacker, vector<Character*>& core, Arena& Arena, int& counter, int& critCounter);
void launchHunt(Character& agent, vector<Character*>& hackTeam, vector<Character*>& core, Arena& Arena, int& counter);

Arena::Arena() {
	Core.push_back(new Server(0));
	bool validInput = false;
	while (validInput == false) {
		cout << "Are the Hackers a Team or going Solo?\n(t) Team\n(s) Solo" << endl;
		cin >> teamMode;
		if (teamMode == 't' || teamMode == 's')
			validInput = true;
		else
			cin.clear();
	}
	int tactic = 0;
	if (teamMode == 't') {
		tactic = 1;
	}
	else {
		tactic = 2;
	}
	for (int i = 0; i < numHaxxers; i++) {
		hackTeam.push_back(new Hacker(i, tactic, Core));
	}
	for (int i = 0; i < numAgents; i++) {
		secTeam.push_back(new Agent(i, 0));
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
	auto startNeuroTimer = chrono::steady_clock::now();
	int x = 0;
	int counter = 0;
	int critCounter = 0;
	thread CoreWatch(watchCore, ref(Core), ref(counter));
	thread Haxxor1(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter), ref(critCounter)); x++;
	thread Haxxor2(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter), ref(critCounter)); x++;
	thread Haxxor3(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter), ref(critCounter)); x++;
	thread Haxxor4(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter), ref(critCounter)); x++;
	thread Haxxor5(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this), ref(counter), ref(critCounter)); x = 0;
	thread Agent1(launchHunt, ref(*secTeam[x]), ref(hackTeam), ref(Core), ref(*this), ref(counter)); x++;
	thread Agent2(launchHunt, ref(*secTeam[x]), ref(hackTeam), ref(Core), ref(*this), ref(counter));
	CoreWatch.join();
	Haxxor1.join();
	Haxxor2.join();
	Haxxor3.join();
	Haxxor4.join();
	Haxxor5.join();
	Agent1.join();
	Agent2.join();

	int pointSum = 0;
	int hpSum = 500;
	for (int i = 0; i < numHaxxers; i++) {
		pointSum += hackTeam[i]->getNum();
	}
	cout << "\nServer HP = " << Core[0]->getHP() << endl;
	cout << "Collective Hacker points = " << pointSum << "\n\nHacker Team" << endl;
	for (int i = 0; i < numHaxxers; i++) {
		if (hackTeam[i]->getLeaderStatus())
			cout << "LEADER ";
		else if(hackTeam[i]->getFormerLeaderStatus())
			cout << "Ex-LEADER ";
		cout << hackTeam[i]->getName() << " made " << hackTeam[i]->getNum() << " points" << endl; 
		cout << "HP left = " << hackTeam[i]->getHP() << endl;
		hpSum -= 100 - hackTeam[i]->getHP();
	}
	cout << "Number of Critical fails = " << critCounter << " dealing a cumulative " << critCounter * 5 << " HP damage" << endl;
	hpSum += critCounter * 5;
	cout << endl << "Server Defense" << endl;
	cout << Core[0]->getName() << " made " << Core[0]->getPoints() << " points" << endl;
	hpSum += Core[0]->getPoints();
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

//tracks how many hackers are still in the game
void watchCore(vector<Character*> Core, int& counter) {
	while (counter < 5) {
		//keep looping
	}
	Core[0]->lockChar.lock();
	Core[0]->setStatus(false);
	Core[0]->lockChar.unlock();
}

void launchAttack(Character& hacker, vector<Character*>& core, Arena& Arena, int& counter, int& critCounter) {
	random_device generator;
	vector<Character*>* hackTeam = Arena.getHackTeam();
	while (hacker.getStatus() && core[0]->getStatus()) {
		hacker.lockChar.lock();
		hacker.setTarget(core);
		hacker.checkLeader(*hackTeam);
		hacker.lockChar.unlock();
		/*Arena.lockArena.lock();
		if (hacker.getLeaderStatus())
			cout << hacker.getName() << " is the current Leader!" << endl;
		Arena.lockArena.unlock();*/
		if (generator() % 100 == 0) {
			hacker.lockChar.lock();
			hacker.setHP(hacker.getHP() - 5);
			Arena.lockArena.lock();
			critCounter++;
			cout << hacker.getName() << " failed critically!" << endl;
			cout << "Hacker HP = " << hacker.getHP() << " | Attack Value = " << hacker.getAttVal() << endl;
			Arena.lockArena.unlock();
			hacker.lockChar.unlock();

		}
		else {
			bool success = hacker.attack(*core[0]);
		}
		int hackerHP = hacker.getHP();
		if (hackerHP % 10 == 0 && hackerHP != 100) {
			hacker.lockChar.lock();
			hacker.setAttVal(hacker.getAttVal() - 2);
			hacker.lockChar.unlock();
		}
		if (hackerHP <= 0 && hacker.getStatus() == true) {
			hacker.lockChar.lock();
			hacker.setStatus(false);
			hacker.setLeaderStatus(false);
			hacker.lockChar.unlock();
			Arena.lockArena.lock();
			cout << hacker.getName() << " has been terminated! " << hacker.getNum() << " points collected" << endl;
			Arena.lockArena.unlock();
		}
	}
	Arena.lockArena.lock();
	counter++;
	Arena.lockArena.unlock();
}

void launchHunt(Character& agent, vector<Character*>& hackTeam, vector<Character*>& core, Arena& Arena, int& counter) {
	random_device generator;
	while (core[0]->getStatus()) {
		agent.setTarget(hackTeam);
		Hacker* hackerTarget = (Hacker*)agent.getTarget();
		if (generator() % 100 < 5) {
			hackerTarget->lockChar.lock();
			if (hackerTarget->getHP() > 0) {
				bool killCheck = false;
				killCheck = agent.attack(*hackerTarget);
				if (killCheck) {
					Arena.lockArena.lock();
					cout << agent.getName() << " eliminated " << hackerTarget->getName() << " | Points: "<< agent.getNum() << endl;
					//counter++;
					Arena.lockArena.unlock();
				}
			}
			hackerTarget->lockChar.unlock();
		}
	}
}

//Trash heap
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