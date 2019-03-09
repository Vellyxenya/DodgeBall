#ifndef ACTOR_H
#define ACTOR_H

#include "tools.h"

class Actor{
	public:
		Actor();
		Actor(Coordinates& inCoos, unsigned int size);
		~Actor();
		
		Coordinates getCoordinates() const;
		
		unsigned int getSize() const;
		
		/*bool isColliding(Actor other){
			if(Tools::norm(coos - other.coos) > size + other.size) return true;
			return false;
		}*/
		
	protected:
		Coordinates coos;
		unsigned int const size; 	//May be the radius(for player/ball) 
									//or half-side(for obstacle)
};

#endif
