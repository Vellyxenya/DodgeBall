#pragma once
#include "tools.h"
#include "actor.h"

class Obstacle{
	public:
		Obstacle(Coordinates& inCoos);
		~Obstacle();
		
	private:
	Coordinates coos;
};
