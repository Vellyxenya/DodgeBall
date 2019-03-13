#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "tools.h"
#include "actor.h"

class Obstacle : public Actor {
	public:
		Obstacle(Coordinates& inCoos, double size);
		~Obstacle();
		
		void analyzePosition(int NbCell); 
		void analyzeDuplication(Obstacle other);
		
	private:

};

#endif
