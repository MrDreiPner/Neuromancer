#include "Server.h"

Server::Server(int x) {
	name = "Mother_Core";
	hp = 100;
	for (int i = 0; i < numDefZones; i++) {
		DefZones.push_back(new Perimeter(i));
	}
	std::cout << name << " the Server has been created!" << std::endl;

}

Server::~Server() {
	for (int i = 0; i < numDefZones; i++) {
		delete(DefZones[i]);
	}
	//std::cout << name << " the Server has been destroyed!" << std::endl;
}

void Server::setTarget(std::vector<Character*>& targetList) {

}

Character* Server::getTarget() {
	return NULL;
}

bool Server::attack(Character& target) {
	return 0;
}