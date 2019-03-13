#ifndef PLAYER_H
#define PLAYER_H

#include "tools.h"
#include "actor.h"

class Player : public Actor{
	public:
		Player();
		Player(	Coordinates& inCoos, double size,
				unsigned int nbTouched, unsigned int coolDown);
		~Player();
		
		void analyzePosition(int index, Coordinates& minDimensions, Coordinates& maxDimensions); 
		
	private:
		int nbTouched, coolDown;
};

#endif
