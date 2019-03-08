#pragma once
#include "tools.h"
#include "actor.h"

class Player : Actor{
	public:
		Player();
		Player(Tools::Coordinates& inCoos, unsigned int size, unsigned int nbTouched, unsigned int coolDown);
		~Player();
		
	private:
		int nbTouched, coolDown;
};
