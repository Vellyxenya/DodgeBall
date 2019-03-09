#include "simulation.h"
#include <iostream>
#include <fstream>
#include <limits>

#define NDEBUG

using namespace std;

Simulation::Simulation(Mode mode, string fileName){
	
	cout << "Using mode : " << mode << endl;
	
	nbCell = -1;
	nbPlayer = -1;
	nbObstacle = -1;
	nbBall = -1;
	
	readData(fileName);
	analyzeData();
	
	map = new Map(nbCell);
	
	cout << "Data read and analyzed" << endl;

}

Simulation::~Simulation(){
	
}

void Simulation::analyzeData(){
	
	Coordinates minDimensions = {-DIM_MAX, -DIM_MAX};
	Coordinates maxDimensions = {DIM_MAX, DIM_MAX};
	
	for (int i(0); i < nbPlayer; ++i) {
		if (!(players[i] -> getCoordinates() <= maxDimensions && 
			players[i] -> getCoordinates() >= minDimensions)) { 	
				
			std::cout << PLAYER_OUT(i+1) << std::endl;
			exit(0);
		} 
	}
	
	for (int i(0); i < nbBall; ++i) {
		if (!(balls[i] -> getCoordinates() <= maxDimensions &&
			balls[i] -> getCoordinates() >= minDimensions)) { 	
				
			std::cout << BALL_OUT(i+1) << std::endl;
			exit(0);
		}
	}
	
	for (int i(0); i < nbObstacle; ++i) {
		
		double x = obstacles[i] -> getCoordinates().x;
		double y = obstacles[i] -> getCoordinates().y;
		
		if (x < 0 || x > nbCell) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(x) << std::endl;
			exit(0);
		} 
			
		if (y < 0 || y > nbCell) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(y) << std::endl;
			exit(0);
		}	
	}  
		
	for (int i(0); i < nbObstacle-1; ++i) { 
		
		Coordinates coosI = obstacles[i] -> getCoordinates();
		
		for (int j(i+1); j < nbObstacle; ++j) { 
			
			Coordinates coosJ = obstacles[j] -> getCoordinates();
			
			if (coosI == coosJ) {
				cout << MULTI_OBSTACLE(coosI.x, coosI.y) << endl; 
				exit(0);
			}
		}
	}
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
	readNumber(file, nbPlayer);
	
	double x,y;
	unsigned int nbTouched, coolDown;
	int i(0);
	
	do{
		std::cout << "do loop" << std::endl;
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
			players.push_back(&player);
			i++;
			file.clear();
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Inserted player : " << i << std::endl;
		}
	} while(i < nbPlayer);
	
	readNumber(file, nbObstacle);
	
	i = 0;
	
	do{
		std::cout << "do loop" << std::endl;
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
			Obstacle obstacle(coos, SIDE/nbCell);
			obstacles.push_back(&obstacle);
			i++;
			file.clear();
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Inserted obstacle : " << i << std::endl;
		}
	} while(i < nbObstacle);
	
	readNumber(file, nbBall);
	
	i = 0;
	double angle;
	
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
			balls.push_back(&ball);
			i++;
			file.clear();
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Inserted ball : " << i << std::endl;
		}
	} while(i < nbBall);

	file.close();
}
