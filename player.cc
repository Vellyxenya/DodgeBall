#include "player.h"

Player::Player(Coordinates& inCoos, unsigned int size,
		unsigned int nbTouched, unsigned int coolDown) :
		Actor(inCoos, size), nbTouched(nbTouched), coolDown(coolDown){
	
}

Player::~Player(){
	
}

void Player::analyzePosition(int index) {
	Actor::analyzePosition(index);
	if (!(coos <= maxDimensions &&  coos >= minDimensions)) { 	
		std::cout << PLAYER_OUT(index+1) << std::endl;
		exit(0);
	}
}
