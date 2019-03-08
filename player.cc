#include "player.h"

Player::Player(Tools::Coordinates& inCoos, unsigned int size,
		unsigned int nbTouched, unsigned int coolDown) :
		Actor(inCoos, size), nbTouched(nbTouched), coolDown(coolDown){
	
}

Player::~Player(){
	
}
