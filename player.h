#ifndef PLAYER_H
#define PLAYER_H

#include "tools.h"
#include "actor.h"

class Player : public Actor{
	public:
		Player();
		Player(	Coordinates& inCoos, unsigned int size,
				unsigned int nbTouched, unsigned int coolDown);
		~Player();

		
	private:
		int nbTouched, coolDown;
};

#endif
