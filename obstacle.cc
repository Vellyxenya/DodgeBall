#include "obstacle.h"

Obstacle::Obstacle(Coordinates& inCoos, unsigned int size) : Actor(inCoos, size){
	
}

Obstacle::~Obstacle(){
	
}

void Obstacle::analyzePosition(int nbCell) {

	if (coos.x < 0 || coos.x > nbCell) { 
		std::cout << OBSTACLE_VALUE_INCORRECT(coos.x) << std::endl;
		exit(0);
	} 
		
	if (coos.y < 0 || coos.y > nbCell) { 
		std::cout << OBSTACLE_VALUE_INCORRECT(coos.y) << std::endl;
		exit(0);
	}
}

void Obstacle::analyzeDuplication(Obstacle other) { 
		
	if (coos == other.coos) {
		std::cout << MULTI_OBSTACLE(coos.x, coos.y) << std::endl; 
		exit(0);
	}
}
