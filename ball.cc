#include "ball.h"


Ball::Ball(Coordinates& inCoos, unsigned int size, double angle) : Actor(inCoos, size), angle(angle){
	
}

void Ball::analyzePositionBall(int i) {
	if ((getCoordinates().x < -200) or (200 <getCoordinates().x) 
		or (getCoordinates().y < -200 ) or (200 < getCoordinates().y)){  
		std::cout << BALL_OUT(i) << std::endl; 
		exit(0);
	}
}

Ball::~Ball(){
	
}
