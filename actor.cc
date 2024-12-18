#include "actor.h"

Actor::Actor(Coordinates& inCoos, double radius) :
			 coos(inCoos), radius(radius){

}

Actor::~Actor(){
	
}

Coordinates Actor::getCoordinates() const{
	return coos;
}

double Actor::getSize() const{
	return radius;
}
