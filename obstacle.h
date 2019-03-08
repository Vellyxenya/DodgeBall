#pragma once
#include "tools.h"
#include "actor.h"

class Obstacle{
	public:
		Obstacle(Tools::Coordinates& inCoos);
		~Obstacle();
		
	private:
	Tools::Coordinates coos;
};
