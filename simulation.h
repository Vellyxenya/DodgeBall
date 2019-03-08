#ifndef 	SIMULATION_H
#define 	SIMULATION_H

#include <vector>
#include "define.h"
#include "tools.h"
#include "map.h"
#include "player.h"
#include "ball.h"
#include "obstacle.h"

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
		void readData(string& fileName); //return if success or not
		void readNumber(ifstream& file, int& value);
		bool analyzeData();
		int nbCell;
		int nbPlayer;
		int nbObstacle;
		int nbBall;
		
		vector<Player> players;	
		vector<Ball> balls;
		vector<Obstacle> obstacles;
		
		//Map map; //Use a pointer instead?
		//Where to read data? Map or Simulation? Better Simulation I think
};

#endif
