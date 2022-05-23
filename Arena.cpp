#include "Arena.h"

using namespace std;

void launchAttack(Character& hacker, vector<Character*>& core, Arena& Arena);
void launchHunt(Character& agent, vector<Character*>& hackTeam, Arena& Arena);

Arena::Arena() {
	Core.push_back(new Server(0));
	for (int i = 0; i < numHaxxers; i++) {
		hackTeam.push_back(new Hacker(i));
	}
	for (int i = 0; i < numAgents; i++) {
		secTeam.push_back(new Agent(i));
	}
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
	int x = 0;
	thread Haxxor1(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this)); x++;
	thread Haxxor2(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this)); x++;
	thread Haxxor3(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this)); x++;
	thread Haxxor4(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this)); x++;
	thread Haxxor5(launchAttack, ref(*hackTeam[x]), ref(Core), ref(*this)); x = 0;
	//thread Agent1(launchHunt, ref(*secTeam[x]), ref(hackTeam), ref(*this)); x++;
	//thread Agent2(launchHunt, ref(*secTeam[x]), ref(hackTeam), ref(*this));
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

	cout << "Server HP = " << Core[0]->getHP() << endl;
	cout << "Collective points = " << sum << endl;
	for (int i = 0; i < numHaxxers; i++) {
		cout << hackTeam[i]->getName() << " made " << hackTeam[i]->getNum() << " points" << endl; 
		cout << "HP left = " << hackTeam[i]->getHP() << endl;
	}

}

void launchAttack(Character& hacker, vector<Character*>& core, Arena& Arena) {
	random_device generator;
	core[0]->lockChar.lock();
	int serverStatus = core[0]->getStatus();
	core[0]->lockChar.unlock();
	hacker.lockChar.lock();
	int hackerStatus = hacker.getStatus();
	hacker.lockChar.unlock();
	while (hackerStatus && serverStatus) {
		//Arena.lockArena.lock();
		hacker.setTarget(core);
		//Arena.lockArena.unlock();
		if (generator() % 100 == 0) {
			hacker.lockChar.lock();
			hacker.setHP(hacker.getHP() - 5);
			hacker.lockChar.unlock();
			/*Arena.lockArena.lock();
			cout << hacker.getName() << " failed critically!" << endl;
			cout << "Hacker HP = " << hacker.getHP() << " | Attack Value = " << hacker.getAttVal() << endl;
			Arena.lockArena.unlock();*/
		}
		else {
			bool success = hacker.attack(*core[0]);
			Character* currTarg = hacker.getPeri(0);
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
		core[0]->lockChar.lock();
		serverStatus = core[0]->getStatus();
		core[0]->lockChar.unlock();
		hacker.lockChar.lock();
		hackerStatus = hacker.getStatus();
		hacker.lockChar.unlock();
	}
}

void launchHunt(Character& agent, vector<Character*>& hackTeam, Arena& Arena) {

}

