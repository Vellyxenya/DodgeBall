#include "player.h"

using namespace std;

Player::Player(Coordinates& inCoos, double size,
		unsigned int nbTouched, unsigned int coolDown) :
		Actor(inCoos, size), nbTouched(nbTouched), coolDown(coolDown){
	
}

Player::~Player(){
	
}

void Player::analyzePosition(int index, Coordinates& minDimensions, Coordinates& maxDimensions) {
	if (!(coos <= maxDimensions &&  coos >= minDimensions)) { 	
		std::cout << PLAYER_OUT(index+1) << std::endl;
		exit(0);
	}
}
