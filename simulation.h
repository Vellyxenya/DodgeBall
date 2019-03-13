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

enum ReadingState{
	NB_CELL,
	NB_PLAYER,
	PLAYERS,
	NB_OBSTACLE,
	OBSTACLES,
	NB_BALL,
	BALLS,
	FINISHED,
	ERROR
};

class Simulation{
	public:
		Simulation(Mode mode, std::string fileName);
		~Simulation();
		
	private:
		Map* map;
	
		void analyzeActors(ActorType actor, int& numberOfActors);
	
		void readData(std::string& fileName); //return if success or not
		
		void analyzeBounds();
		
		void retrievePlayers(	std::istringstream& stream,
								ReadingState& state, int& counter);
		void retrieveBalls(		std::istringstream& stream,
								ReadingState& state, int& counter);
		void retrieveObstacles(	std::istringstream& stream,
								ReadingState& state, int& counter);
		void retrieveNbCell(	std::istringstream& stream,
								ReadingState& state);
		void retrieveNbPlayer(	std::istringstream& stream,
								ReadingState& state);
		void retrieveNbObstacle(std::istringstream& stream,
								ReadingState& state);
		void retrieveNbBall(	std::istringstream& stream,
								ReadingState& state);						
	
};

#endif
