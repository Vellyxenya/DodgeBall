#pragma once
#include "actor.h"
#include "define.h"

class Map{
	public:
		
		Map(int const nbCell);
		~Map();
		
		template <typename T, typename S>
		bool isColliding(const T& a, const T& b);
		
		bool isInMap(Actor actor, double securityMargin);
		
	private:
		unsigned int nbCell;
		double ML;
		double MJ;
	
};
