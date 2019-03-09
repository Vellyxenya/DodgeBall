#include "string"
#include "tools.h"

bool Tools::isTxtFile(std::string fileName){
	if(fileName.substr(fileName.rfind(".")+1) == "txt")
		return true;
	return false;
}

double Tools::norm(Coordinates coo){
	return sqrt(coo.x*coo.x+coo.y*coo.y);
}

bool Coordinates::operator<=(Coordinates& other){
	if (x <= other.x && y <= other.y) return true;
	return false;
}

bool Coordinates::operator>=(Coordinates& other){
	if (x >= other.x && y >= other.y) return true;
	return false;
}
	
bool Coordinates::operator==(Coordinates& other){
	if (x == other.x && y == other.y) return true;
	return false;
}
	
Coordinates Coordinates::operator-(Coordinates& other){
	double dx = x - other.x;
	double dy = y - other.y;
	return {dx, dy};
}
