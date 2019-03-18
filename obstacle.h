#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "tools.h"
#include "error.h"

class Obstacle {
	public:
		Obstacle(Coordinates& inCoos, double halfSide);
		~Obstacle();
		
		void analyzePosition(int NbCell); 
		void analyzeDuplication(Obstacle* other);
		
		Coordinates getCoordinates() const;
		double getSize() const;
		
	private:
		Coordinates coos;
		double halfSide;
};

#endif
