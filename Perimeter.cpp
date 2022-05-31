#include "Perimeter.h"

Perimeter::Perimeter(int x) {
	ID = x;
	nameID = ID + 1;
	cout << "DefZone " << nameID << " established!" << endl;
}

Perimeter::~Perimeter(){
	//cout << "DefZone " << nameID << " deleted!" << endl;
}

