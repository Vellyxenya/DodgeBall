#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include "tools.h"
#include "error.h"

class Actor{
	public:
		Actor();
		Actor(Coordinates& inCoos, double size);
		~Actor();
		
		Coordinates getCoordinates() const;
		double getSize() const;

	protected:
		Coordinates coos;
		double size; 	//radius(for player/ball) 
						//half-side(for obstacle)
};

#endif
