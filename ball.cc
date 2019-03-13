#include "ball.h"

Ball::Ball(Coordinates& inCoos, double size, double angle) : Actor(inCoos, size), angle(angle){
	
}

Ball::~Ball(){
	
}

void Ball::analyzePosition(int index, Coordinates& minDimensions, Coordinates& maxDimensions) {
	if (!(coos <= maxDimensions && coos >= minDimensions)) { 	
		std::cout << BALL_OUT(index+1) << std::endl;
		exit(0);
	}
}
