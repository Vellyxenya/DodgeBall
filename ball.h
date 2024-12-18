#ifndef BALL_H
#define BALL_H

#include "tools.h"
#include "actor.h"

class Ball : public Actor{
	public:
		Ball(Coordinates& inCoos, double size, double angle);
		~Ball();
		
		void analyzePosition(int index, Coordinates& minDimensions,
							 Coordinates& maxDimensions);
		
	private:
		double angle;
};

#endif
