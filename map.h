#ifndef MAP_H
#define MAP_H

#include "actor.h"
#include "define.h"

class Map{
	public:
		
		Map(int nbCell);
		~Map();
		
		//Player-Player, Player-Ball, Ball-Ball
		bool isColliding(Actor actor1, Actor actor2);
		
		/*template <typename T, typename S>
		bool isColliding(const T& a, const T& b);*/
		
	private:
		unsigned int nbCell;
		double ML;
		double MJ;
	
};

#endif
