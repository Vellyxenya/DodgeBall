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

double Tools::distance(Coordinates coo1, Coordinates coo2){
	return norm(coo1 - coo2);
}

double Tools::getHypothenus(double a, double b){
	return sqrt(a*a+b*b);
}

bool Tools::isInSquare(Coordinates coos, Square square) {
	Coordinates vertexTranslation = {square.halfSide, square.halfSide}; //Is this a magic number??
	Coordinates min = square.coos - vertexTranslation;
	Coordinates max = square.coos + vertexTranslation;
	if(coos >= min && coos <= max){
		return true;
	}
	return false;
}
bool Tools::isInCircle(Coordinates coos, Circle circle) {
	if(Tools::distance(coos, circle.coos) <= circle.radius){
		return true;
	}
	return false;
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

Coordinates Coordinates::operator+(Coordinates& other){
	double dx = x + other.x;
	double dy = y + other.y;
	return {dx, dy};
}
