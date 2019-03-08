#pragma once
#include "tools.h"
#include "actor.h"

class Player : public Actor{
	public:
		Player();
		Player(Coordinates& inCoos, unsigned int size, unsigned int nbTouched, unsigned int coolDown);
		~Player();
		void randomFunction(){
			
		};

		
	private:
		int nbTouched, coolDown;
};
