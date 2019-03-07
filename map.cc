#include "map.h"

Map::Map(int nbCell) : 	nbCell(nbCell),
						MJ(COEF_MARGE_JEU * (SIDE/nbCell)),
						ML(COEF_MARGE_JEU/2 * (SIDE/nbCell)){
	
}

bool Map::isInMap(Actor actor, double securityMargin){
			
	double x = actor.getCoordinates().x;
	double y = actor.getCoordinates().y;
	double s = actor.getSize();
	
	if(	(x + s + securityMargin) >= DIM_MAX  ||
		(x - s - securityMargin) <= -DIM_MAX ||
		(y + s + securityMargin) >= DIM_MAX  ||
		(y - s - securityMargin) <= -DIM_MAX){
		return false;
	}
	return true;
}

template <typename T, typename S>
bool Map::isColliding(const T& a, const T& b){
	
	
	
	
	return true;
}
