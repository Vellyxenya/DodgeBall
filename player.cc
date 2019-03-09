#include "player.h"


Player::Player(Coordinates& inCoos, unsigned int size,
		unsigned int nbTouched, unsigned int coolDown) :
		Actor(inCoos, size), nbTouched(nbTouched), coolDown(coolDown){
	
}

void Player::analyzePositionPlayer(int i) {
	
	if ((getCoordinates().x < -200) or (200 <getCoordinates().x) 
		or (getCoordinates().y < -200 ) or (200 < getCoordinates().y)){  
		std::cout << PLAYER_OUT(i) << std::endl; 
		exit(0);
	}
}

Player::~Player(){
	
}
