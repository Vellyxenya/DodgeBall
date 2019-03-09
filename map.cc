#include "map.h"

Map::Map(int nbCell) : 	nbCell(nbCell) {
	MJ = COEF_MARGE_JEU * (SIDE/nbCell);
	ML = COEF_MARGE_JEU/2 * (SIDE/nbCell);
}

//Player-Player, Player-Ball, Ball-Ball
bool Map::isColliding(Actor actor1, Actor actor2){
	Coordinates coos1 = actor1.getCoordinates();
	Coordinates coos2 = actor2.getCoordinates();
	double size1 = actor1.getSize();
	double size2 = actor2.getSize();
	
	if (Tools::norm(coos1 - coos2) < (size1 + size2 + ML)) {
		return true;
	}
	return false;
}


/*template <typename T, typename S>
bool Map::isColliding(const T& a, const T& b){
	return true;
}*/
