#include "simulation.h"
#include <iostream>
#include <fstream>
#include <limits>

#define NDEBUG
#define INVALID_VALUE -1

//Maybe remove this std??
using namespace std;

Simulation::~Simulation(){
	
}

Simulation::Simulation(Mode mode, string fileName){
	
	cout << "Using mode : " << mode << endl;
	
	nbCell = INVALID_VALUE;
	nbPlayer = INVALID_VALUE;
	nbObstacle = INVALID_VALUE;
	nbBall = INVALID_VALUE;

	readData(fileName);
	
	analyzeData();
	
	map->detectCollisions();
}

void Simulation::analyzeData(){
	Coordinates minDimensions = {-DIM_MAX, -DIM_MAX};
	Coordinates maxDimensions = {DIM_MAX, DIM_MAX};
	
	for (int i(0); i < nbPlayer; ++i) {
		Coordinates coos = map->getPlayers()[i].getCoordinates();
		if (!(coos <= maxDimensions &&  coos >= minDimensions)) { 	
				
			std::cout << PLAYER_OUT(i+1) << std::endl;
			exit(0);
		} 
	}
	
	cout << "Players ok" << endl;
	
	for (int i(0); i < nbBall; ++i) {
		Coordinates coos = map->getBalls()[i].getCoordinates();
		if (!(coos <= maxDimensions && coos >= minDimensions)) { 	
				
			std::cout << BALL_OUT(i+1) << std::endl;
			exit(0);
		}
	}
	
	cout << "Balls ok" << endl;
	
	for (int i(0); i < nbObstacle; ++i) {
		
		double x = map->getObstacles()[i].getCoordinates().x;
		double y = map->getObstacles()[i].getCoordinates().y;
		
		if (x < 0 || x > nbCell) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(x) << std::endl;
			exit(0);
		} 
			
		if (y < 0 || y > nbCell) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(y) << std::endl;
			exit(0);
		}	
	}  
	
	cout << "Obstacles ok 1" << endl;
		
	for (int i(0); i < nbObstacle-1; ++i) { 
		
		Coordinates coosI = map->getObstacles()[i].getCoordinates();
		
		for (int j(i+1); j < nbObstacle; ++j) { 
			Coordinates coosJ = map->getObstacles()[j].getCoordinates();
			
			if (coosI == coosJ) {
				cout << MULTI_OBSTACLE(coosI.x, coosI.y) << endl; 
				exit(0);
			}
		}
	}
	
	cout << "Obstacles ok 2" << endl;
	cout << "Data read and analyzed" << endl;
}

void Simulation::readNumber(ifstream& file, int& value){
	while(value == -1){
		cout << "while loop" << endl;
		if(!(file >> value)){  //Echec
			if(file.eof()){
				cout << value << endl;
				cout << "fin du fichier, fichier incorrect, 1" << endl;
				break;
			} else {
				file.clear();
				file.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "clearing" << endl;
				value = -1;
			}
		}
		std::cout << "Valeur : " << value << std::endl;
	}
}

void Simulation::readData(string& fileName){
	
	ifstream file;
	file.open(fileName);
	if(file.fail()) {
		cout << "failed to open file" << endl;
		exit(0);
	}
			
	readNumber(file, nbCell);
	
	map = new Map(nbCell);
	
	readNumber(file, nbPlayer);
	
	retrievePlayers(file);
	
	readNumber(file, nbObstacle);
	
	retrieveObstacles(file);
	
	readNumber(file, nbBall);
	
	retrieveBalls(file);

	file.close();
}

void Simulation::retrievePlayers(ifstream& file){
	double x,y;
	unsigned int nbTouched, coolDown;
	int i(0);

	do{
		if(!(file >> x >> y >> nbTouched >> coolDown)){  //Echec
			if(file.eof()){
				cout << "fin du fichier, fichier incorrect" << endl;
				break;
			} else {
				file.clear();
				file.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "clearing" << endl;
			}
		} else {
			Coordinates coos = {x,y};
			Player player(coos, COEF_RAYON_JOUEUR*nbCell, nbTouched, coolDown);
			map->getPlayers().push_back(player);
			i++;
			file.clear();
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Inserted player : " << i << std::endl;
		}
	} while(i < nbPlayer);
}

void Simulation::retrieveObstacles(ifstream& file){
	int i(0);
	double x, y;
	
	do{
		if(!(file >> x >> y)){  //Echec
			if(file.eof()){
				cout << "fin du fichier, fichier incorrect" << endl;
				break;
			} else {
				file.clear();
				file.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "clearing" << endl;
			}
		} else {
			Coordinates coos = {x,y};
			Obstacle obstacle(coos, SIDE/nbCell/2);
			map->getObstacles().push_back(obstacle);
			std::cout << "Obstacle size " << map->getObstacles()[i].getSize() << std::endl;
			i++;
			file.clear();
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Inserted obstacle : " << i << std::endl;
		}
	} while(i < nbObstacle);
}

void Simulation::retrieveBalls(ifstream& file){
	int i(0);
	double x,y, angle;
	
	do{
		std::cout << "do loop" << std::endl;
		if(!(file >> x >> y >> angle)){  //Echec
			if(file.eof()){
				cout << "fin du fichier, fichier incorrect" << endl;
				break;
			} else {
				file.clear();
				file.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "clearing" << endl;
			}
		} else {
			Coordinates coos = {x,y};
			Ball ball(coos, COEF_RAYON_BALLE*nbCell, angle);
			map->getBalls().push_back(ball);
			i++;
			file.clear();
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Inserted ball : " << i << std::endl;
		}
	} while(i < nbBall);
}
