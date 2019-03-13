#include "simulation.h"
#include <fstream>

#define NDEBUG

using namespace std;

Simulation::~Simulation(){
	
}

Simulation::Simulation(Mode mode, string fileName){
	cout << "Using mode : " << mode << endl;
	
	readData(fileName);
	
	map->analyzeBounds();
	map->detectCollisions();
	delete map;
	
	cout << FILE_READING_SUCCESS << endl;
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
					cout << "An Error occured while reading the file" << endl;
					exit(0);
			}
		}
	} else {
		cout << "Failed to open file : " << fileName << endl;
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
		if(nbTouched >= 0 && nbTouched <= MAX_TOUCH &&
			coolDown >= 0 && coolDown <= MAX_COUNT){
			Coordinates coos = {x,y};
			Player player(coos, COEF_RAYON_JOUEUR*(SIDE/map->getNbCell()), nbTouched, coolDown);
			map->getPlayers().push_back(player);
			counter++;
			if(counter == map->getNbPlayer()) {
				state = NB_OBSTACLE;
				counter = 0;
			}
		} else state = ERROR;
	} else state = ERROR;
}

void Simulation::retrieveObstacles(istringstream& stream,
								   ReadingState& state, int& counter){
	int line, column;
	if(stream >> line >> column) {
		Coordinates coos = {(double)line, (double)column}; //see for this...
		Obstacle obstacle(coos, SIDE/map->getNbCell()/2);
		map->getObstacles().push_back(obstacle); //Comment push_back des pointers sans perdre les coordonnées
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
		Ball ball(coos, COEF_RAYON_BALLE*(SIDE/map->getNbCell()), angle);
		cout << map->getNbCell() << endl;
		map->getBalls().push_back(ball);
		counter++;
		if(counter == map->getNbBall()) {
			state = FINISHED;
			counter = 0;
		}
	} else state = ERROR;
}
