#include "Server.h"

Server::Server() {
	name = "Mother_Core";
	hp = 100;
	points = 0;
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