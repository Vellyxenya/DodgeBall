#include "ball.h"

Ball::Ball(Coordinates& inCoos, unsigned int size, double angle) : Actor(inCoos, size), angle(angle){
	
}

Ball::~Ball(){
	
}

void Ball::analyzePosition(int index) {
	Actor::analyzePosition(index);
	if (!(coos <= maxDimensions && coos >= minDimensions)) { 	
		std::cout << BALL_OUT(index+1) << std::endl;
		exit(0);
	}
}
