#include "obstacle.h"

Obstacle::Obstacle(Coordinates& inCoos, unsigned int size) : Actor(inCoos, size){
	
}



void Obstacle::analyzePositionObstacle(int& nbCell) {
	
	if ((getCoordinates().x < 0 ) or (nbCell < getCoordinates().x)) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(getCoordinates().x) << std::endl;
			exit(0);
	} 
			
		
	if ((getCoordinates().y < 0) or (nbCell <getCoordinates().y)) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(getCoordinates().y) << std::endl;
			exit(0);
	}
}

void Obstacle::analyzeDuplicationObstacle( Obstacle obstacle2) { 
	
	if ( (getCoordinates().x == obstacle2.getCoordinates().x) and (getCoordinates().y == obstacle2.getCoordinates().y) ) {
				std::cout << MULTI_OBSTACLE(getCoordinates().x, getCoordinates().y) << std::endl; 
				exit(0);
	}
}	



Obstacle::~Obstacle(){
	
}
