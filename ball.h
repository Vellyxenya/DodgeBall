#pragma once
#include "tools.h"
#include "actor.h"
#include "error.h" 
#include <iostream> 

class Ball : public Actor{
	public:
		Ball(Coordinates& inCoos, unsigned int size, double angle);
		~Ball();
		
		void analyzePositionBall(int i);
		
	private:
		double angle;
};
