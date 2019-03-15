#include "simulation.h"
#include <fstream>
#include <iostream>

using namespace std;

#define FIRST_INDEX 0

Simulation::~Simulation(){
	
}

Simulation::Simulation(Mode mode, string fileName){
	
	readData(fileName);
	
	map->analyzeBounds();
	map->detectCollisions();
	delete map;
	
	cout << FILE_READING_SUCCESS << endl;
}

void Simulation::readData(string& fileName){
	
	ReadingState state(NB_CELL);
	string line;
	
	ifstream file(fileName);
	if(!file.fail()) {
		while(getline(file >> ws, line) && state != FINISHED) {
			if(line[FIRST_INDEX] == '#') continue;
			istringstream stream(line);
			
			switch(state) {
				case NB_CELL :
					retrieveNbCell(stream, state); break;
				case NB_PLAYER :
					retrieveNbPlayer(stream, state); break;
				case PLAYERS :
					retrievePlayers(stream, state); break;
				case NB_OBSTACLE :
					retrieveNbObstacle(stream, state); break;
				case OBSTACLES :
					retrieveObstacles(stream, state); break;
				case NB_BALL :
					retrieveNbBall(stream, state); break;
				case BALLS :
					retrieveBalls(stream, state); break;
				case FINISHED : break;
				case ERROR :
					cerr << "Reading error" << endl;
					file.close();
					exit(0);
			}
		}
	} else {
		cerr << "Failed to open : " << fileName << endl;
		exit(0);
	}
	file.close();
}

void Simulation::retrieveNbCell(std::istringstream& stream,
								ReadingState& state){
	int nbCell;
	stream >> nbCell;
	if (nbCell >= MIN_CELL && nbCell <= MAX_CELL) {
		map = new Map(nbCell);
		state = NB_PLAYER;
	} else state = ERROR;						
}

void Simulation::retrieveNbPlayer(std::istringstream& stream,
								  ReadingState& state){
	int nbPlayer;
	stream >> nbPlayer;
	if(map->setNbPlayer(nbPlayer)) {
		state = PLAYERS;
	} else state = ERROR;
}

void Simulation::retrieveNbObstacle(std::istringstream& stream,
									ReadingState& state){
	int nbObstacle;
	stream >> nbObstacle;
	if(map->setNbObstacle(nbObstacle)) {
		state = OBSTACLES;
	} else state = ERROR;
}

void Simulation::retrieveNbBall(std::istringstream& stream,
								ReadingState& state){
	int nbBall;
	stream >> nbBall;
	if(map->setNbBall(nbBall)) {
		state = BALLS;
	} else state = ERROR;
}

void Simulation::retrievePlayers(istringstream& stream,
								 ReadingState& state) {
	static unsigned int counter(0);
	double x, y;
	int nbTouched, coolDown;
	if(stream >> x >> y >> nbTouched >> coolDown){
		if(nbTouched >= 0 && nbTouched <= MAX_TOUCH &&
			coolDown >= 0 && coolDown <= MAX_COUNT) {
			Coordinates coos = {x,y};
			Player* player = new Player(coos,
				COEF_RAYON_JOUEUR*(SIDE/map->getNbCell()),
				nbTouched, coolDown);
			map->getPlayers().push_back(player);
			counter++;
			if(counter == map->getNbPlayer()) state = NB_OBSTACLE;
		} else state = ERROR;
	} else state = ERROR;
}

void Simulation::retrieveObstacles(istringstream& stream,
								   ReadingState& state){
	static unsigned int counter(0);
	int line, column;
	if(stream >> line >> column) {
		Coordinates coos = {static_cast<double>(line),
							static_cast<double>(column)};
		Obstacle* obstacle = new Obstacle(coos,
										  SIDE/map->getNbCell()/2);
		map->getObstacles().push_back(obstacle);
		counter++;
		if(counter == map->getNbObstacle()) state = NB_BALL;
	} else state = ERROR;
}

void Simulation::retrieveBalls(istringstream& stream,
							   ReadingState& state){
	static unsigned int counter(0);
	double x, y, angle;
	if(stream >> x >> y >> angle) {
		Coordinates coos = {x,y};
		Ball* ball = new Ball(coos, COEF_RAYON_BALLE*
							  (SIDE/map->getNbCell()), angle);
		map->getBalls().push_back(ball);
		counter++;
		if(counter == map->getNbBall()) state = FINISHED;
	} else state = ERROR;
}
