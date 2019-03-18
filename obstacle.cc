#include <iostream>

#include "obstacle.h"

using namespace std;

Obstacle::Obstacle(Coordinates& inCoos, double halfSide) :
				   coos(inCoos), halfSide(halfSide) {
	
}

Obstacle::~Obstacle(){
	
}

Coordinates Obstacle::getCoordinates() const{
	return coos;
}

double Obstacle::getSize() const{
	return halfSide;
}

void Obstacle::analyzePosition(int nbCell) {

	if (coos.x < 0 || coos.x >= nbCell) { 
		cerr << OBSTACLE_VALUE_INCORRECT(static_cast<int>(coos.x))
		<< endl;
		exit(0);
	} 
		
	if (coos.y < 0 || coos.y >= nbCell) { 
		cerr << OBSTACLE_VALUE_INCORRECT(static_cast<int>(coos.y))
		<< endl;
		exit(0);
	}
}

void Obstacle::analyzeDuplication(Obstacle* other) { 
		
	if (coos == other->coos) {
		cerr << MULTI_OBSTACLE((static_cast<int>(coos.x)),
		(static_cast<int>(coos.y))) << endl;
		exit(0);
	}
}
