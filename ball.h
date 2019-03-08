#pragma once
#include "tools.h"
#include "actor.h"

class Ball : Actor{
	public:
		Ball(Tools::Coordinates& inCoos, unsigned int size, double angle);
		~Ball();
		
	private:
		double angle;
};
