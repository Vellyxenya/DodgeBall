#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include "tools.h"
#include "error.h"

class Actor{
	public:
		Actor();
		Actor(Coordinates& inCoos, unsigned int size);
		~Actor();
		
		virtual void analyzePosition(int index);
		
		Coordinates getCoordinates() const;
		double getSize() const;

	protected:
		Coordinates minDimensions;
		Coordinates maxDimensions;
		Coordinates coos;
		double size; 	//May be the radius(for player/ball) 
									//or half-side(for obstacle)
};

#endif
