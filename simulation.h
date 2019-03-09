#ifndef 	SIMULATION_H
#define 	SIMULATION_H

#include <fstream>
#include <vector>
#include "define.h"
#include "tools.h"
#include "map.h"
#include "error.h" 

enum Mode{
	Error,
	Step,
	Normal
};

class Simulation{
	public:
		Simulation(Mode mode, std::string fileName);
		~Simulation();
		
	private:
		void readData(std::string& fileName); //return if success or not
		void readNumber(std::ifstream& file, int& value);
		void analyzeData();
		
		void retrievePlayers(std::ifstream& file);
		void retrieveBalls(std::ifstream& file);
		void retrieveObstacles(std::ifstream& file);
		
		int nbCell;
		int nbPlayer;
		int nbObstacle;
		int nbBall;
		
		Map* map;

};

#endif
