#pragma once
#include "tools.h"
#include "actor.h"
#include <iostream> 
#include "error.h" 

class Player : public Actor{
	public:
		Player();
		Player(Coordinates& inCoos, unsigned int size, unsigned int nbTouched, unsigned int coolDown);
		~Player();
		void randomFunction(){
	
		};
		void analyzePositionPlayer(int i); 
		
	private:
		int nbTouched, coolDown;
};
