#include "simulation.h"
#include <fstream>

#define NDEBUG
#define INVALID_VALUE -1

using namespace std;

Simulation::~Simulation(){
	
}

Simulation::Simulation(Mode mode, string fileName){
	cout << "Using mode : " << mode << endl;
	nbCell = INVALID_VALUE;
	
	readData(fileName);
	
	map->analyzeData();
	map->detectCollisions();
}

void Simulation::readData(string& fileName){
	
	ReadingState state(NB_CELL);
	string line;
	int counter(0);
	
	ifstream file(fileName);
	if(!file.fail()) {
		while(getline(file >> ws, line) && state != FINISHED) {
			if(line[0] == '#') continue;
			istringstream stream(line);
			
			switch(state) {
				case NB_CELL :
					retrieveNbCell(stream, state); break;
				case NB_PLAYER :
					retrieveNbPlayer(stream, state); break;
				case PLAYERS :
					retrievePlayers(stream, state, counter); break;
				case NB_OBSTACLE :
					retrieveNbObstacle(stream, state); break;
				case OBSTACLES :
					retrieveObstacles(stream, state, counter); break;
				case NB_BALL :
					retrieveNbBall(stream, state); break;
				case BALLS :
					retrieveBalls(stream, state, counter); break;
				case FINISHED : break;
				case ERROR :
					cout << "Error" << endl;
					exit(0);
			}
		}
		cout << "FINISHED READING" << endl;
	} else {
		cout << "Failed to open file : " << fileName << endl;
		exit(0);
	}
	file.close();
}

void Simulation::retrieveNbCell(std::istringstream& stream,
								ReadingState& state){
	stream >> nbCell;
	if (nbCell >= MIN_CELL && nbCell <= MAX_CELL) {
		map = new Map(nbCell);
		state = NB_PLAYER;
		cout << "nbCell : " << nbCell << endl;
	} else state = ERROR;						
}

void Simulation::retrieveNbPlayer(std::istringstream& stream,
								  ReadingState& state){
	int nbPlayer;
	stream >> nbPlayer; //isn't 0 the default value for a false reading?
	if(nbPlayer >= 0) {
		map->setNbPlayer(nbPlayer);
		state = PLAYERS;
	} else state = ERROR;
}

void Simulation::retrieveNbObstacle(std::istringstream& stream,
									ReadingState& state){
	int nbObstacle;
	stream >> nbObstacle;
	if(nbObstacle >= 0) {
		map->setNbObstacle(nbObstacle);
		state = OBSTACLES;
	} else state = ERROR;
}

void Simulation::retrieveNbBall(std::istringstream& stream,
								ReadingState& state){
	int nbBall;
	stream >> nbBall;
	if(nbBall >= 0) {
		map->setNbBall(nbBall);
		state = BALLS;
	} else state = ERROR;
}

void Simulation::retrievePlayers(istringstream& stream,
								 ReadingState& state, int& counter){
	double x, y;
	int nbTouched, coolDown;
	if(stream >> x >> y >> nbTouched >> coolDown){
		Coordinates coos = {x,y};
		Player player(coos, COEF_RAYON_JOUEUR*nbCell, nbTouched, coolDown);
		map->getPlayers().push_back(player);
		counter++;
		if(counter == map->getNbPlayer()) {
			state = NB_OBSTACLE;
			counter = 0;
		}
	} else state = ERROR;
}

void Simulation::retrieveObstacles(istringstream& stream,
								   ReadingState& state, int& counter){
	int line, column;
	if(stream >> line >> column) {
		Coordinates coos = {(double)line, (double)column}; //see for this...
		Obstacle obstacle(coos, SIDE/nbCell/2);
		map->getObstacles().push_back(obstacle);
		counter++;
		if(counter == map->getNbObstacle()) {
			state = NB_BALL;
			counter = 0;
		}
	} else state = ERROR;
}

void Simulation::retrieveBalls(istringstream& stream,
							   ReadingState& state, int& counter){
	double x, y, angle;
	if(stream >> x >> y >> angle) {
		Coordinates coos = {x,y};
		Ball ball(coos, COEF_RAYON_BALLE*nbCell, angle);
		map->getBalls().push_back(ball);
		counter++;
		if(counter == map->getNbBall()) {
			state = FINISHED;
			counter = 0;
		}
	} else state = ERROR;
}
