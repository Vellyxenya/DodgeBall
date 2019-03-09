#pragma once
#include "tools.h"
#include "actor.h"
#include "error.h" 
#include <iostream> 

class Obstacle : public Actor {
	public:
		Obstacle(Coordinates& inCoos, unsigned int size);
		~Obstacle();
		
		
		void analyzePositionObstacle(int& NbCell); 
		void analyzeDuplicationObstacle( Obstacle obstacle2);

		
	private:
	//Coordinates coos;
};
