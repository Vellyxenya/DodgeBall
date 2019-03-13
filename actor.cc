#include "actor.h"

Actor::Actor(Coordinates& inCoos, double size) : coos(inCoos), size(size){

}

Actor::~Actor(){
	
}

Coordinates Actor::getCoordinates() const{
	return coos;
}

double Actor::getSize() const{
	return size;
}
