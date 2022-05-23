#include <iostream>
#include <chrono>
#include "Arena.h"

int main() {
	auto startTimer = std::chrono::steady_clock::now();
	std::cout << "Welcome to NEUROMANCER" << std::endl;
	Arena* HaxFest = new Arena();
	HaxFest->startBreach();
	delete(HaxFest);
	auto endTimer = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startTimer).count();
	std::cout << "Runtime - entire program: " << elapsed << " ms" << std::endl;
	return 0;
}

