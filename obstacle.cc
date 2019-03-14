#include "obstacle.h"

using namespace std;

Obstacle::Obstacle(Coordinates& inCoos, double size) : Actor(inCoos, size){
	
}

Obstacle::~Obstacle(){
	
}

void Obstacle::analyzePosition(int nbCell) {

	if (coos.x < 0 || coos.x >= nbCell) { 
		cout << OBSTACLE_VALUE_INCORRECT(static_cast<int>(coos.x))
		<< endl;
		exit(0);
	} 
		
	if (coos.y < 0 || coos.y >= nbCell) { 
		cout << OBSTACLE_VALUE_INCORRECT(static_cast<int>(coos.y))
		<< endl;
		exit(0);
	}
}

void Obstacle::analyzeDuplication(Obstacle* other) { 
		
	if (coos == other->coos) {
		cout << MULTI_OBSTACLE((static_cast<int>(coos.x)),
		(static_cast<int>(coos.y))) << endl; 
		exit(0);
	}
}
