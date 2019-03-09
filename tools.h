#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <cmath>

/**
 * Utility functions, structs...
 */

struct Coordinates{
	double x;
	double y;
	
	bool operator<=(Coordinates& other);
	bool operator>=(Coordinates& other);
	bool operator==(Coordinates& other);
	Coordinates operator-(Coordinates& other);
	Coordinates operator+(Coordinates& other);
};

struct Square{
	Coordinates coos;
	double halfSide;
};

struct Circle{
	Coordinates coos;
	double radius;
};
 
class Tools{
	public:
		//Is it a problem to declaire this static?
		static bool isTxtFile(std::string fileName);
		static double norm(Coordinates coo);
		static double distance(Coordinates coo1, Coordinates coo2);
		static bool isInSquare(Coordinates coos, Square square);
		static bool isInCircle(Coordinates coos, Circle circle);
		
	private:
	
};

#endif
