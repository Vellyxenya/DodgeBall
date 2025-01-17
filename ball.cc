#include <iostream>

#include "ball.h"

using namespace std;

Ball::Ball(Coordinates& inCoos, double size, double angle) :
		   Actor(inCoos, size), angle(angle) {
	
}

Ball::~Ball(){
	
}

void Ball::analyzePosition(int index, Coordinates& minDimensions,
						   Coordinates& maxDimensions) {
							   
	if (!(coos <= maxDimensions && coos >= minDimensions)) { 	
		cout << BALL_OUT(index+1) << endl;
		exit(0);
	}
}
