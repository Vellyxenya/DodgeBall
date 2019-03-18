#ifndef ACTOR_H
#define ACTOR_H

#include "tools.h"
#include "error.h"

class Actor{
	public:
		Actor();
		Actor(Coordinates& inCoos, double radius);
		~Actor();
		
		Coordinates getCoordinates() const;
		double getSize() const;

	protected:
		Coordinates coos;
		double radius;
};

#endif
