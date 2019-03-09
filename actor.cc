#include "actor.h"
#include <iostream>

Actor::Actor(Coordinates& inCoos, unsigned int size) : coos(inCoos), size(size){

}

Actor::~Actor(){
	
}

Coordinates Actor::getCoordinates() const{
	return coos;
}

unsigned int Actor::getSize() const{
	return size;
}
