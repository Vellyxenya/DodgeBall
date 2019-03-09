#pragma once
#include "tools.h"
#include "actor.h"

class Obstacle : public Actor {
	public:
		Obstacle(Coordinates& inCoos, unsigned int size);
		~Obstacle();
		
	private:
	//Coordinates coos;
};
