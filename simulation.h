#pragma once
#include "tools.h"
#include "map.h"

using namespace std;

enum Mode{
	Error,
	Step,
	Normal
};

class Simulation{
	public:
		Simulation(Mode mode, string fileName);
		~Simulation();
		
	private:
		bool readData(string& fileName); //return if success or not
		//Map map; //Use a pointer instead?
		//Where to read data? Map or Simulation? Better Simulation I think
};
