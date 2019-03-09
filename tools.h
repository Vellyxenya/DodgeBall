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
};
 
class Tools{
	public:
		//Is it a problem to declaire this static?
		static bool isTxtFile(std::string fileName);
		static double norm(Coordinates coo);
		
	private:
	
};

#endif
