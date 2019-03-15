#ifndef 	SIMULATION_H
#define 	SIMULATION_H

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
	
		void readData(std::string& fileName);
		
		void retrievePlayers(	std::istringstream& stream,
								ReadingState& state);
		void retrieveBalls(		std::istringstream& stream,
								ReadingState& state);
		void retrieveObstacles(	std::istringstream& stream,
								ReadingState& state);
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
