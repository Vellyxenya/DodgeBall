#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "tools.h"
#include "actor.h"

class Obstacle : public Actor {
	public:
		Obstacle(Coordinates& inCoos, unsigned int size);
		~Obstacle();
		
		void analyzePosition(int NbCell) override; 
		void analyzeDuplication(Obstacle other);
		
	private:

};

#endif
