#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "tools.h"
#include "actor.h"

class Obstacle : public Actor {
	public:
		Obstacle(Coordinates& inCoos, unsigned int size);
		~Obstacle();
		
	private:

};

#endif
