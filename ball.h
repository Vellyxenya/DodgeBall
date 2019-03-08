#pragma once
#include "tools.h"
#include "actor.h"

class Ball : public Actor{
	public:
		Ball(Coordinates& inCoos, unsigned int size, double angle);
		~Ball();
		
	private:
		double angle;
};
