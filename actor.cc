#include "actor.h"
#include <iostream>

Actor::Actor(Coordinates& inCoos, unsigned int size) : coos(inCoos), size(size){

}

Actor::~Actor(){
	
}

void Actor::analyzePosition(int index){ //A voir
	minDimensions = {-DIM_MAX, -DIM_MAX};
	maxDimensions = {DIM_MAX, DIM_MAX};
}

Coordinates Actor::getCoordinates() const{
	return coos;
}

double Actor::getSize() const{
	return size;
}
