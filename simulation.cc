
#include "simulation.h"
#include <iostream>
#include <fstream>
#include <limits>

#define NDEBUG

using namespace std;

Simulation::Simulation(Mode mode, string fileName){
	std::cout << "Using mode : " << mode << std::endl;
	nbCell = -1;
	nbPlayer = -1;
	nbObstacle = -1;
	nbBall = -1;
	readData(fileName);
	analyzeData();
	
	std::cout << "Data read and analyzed" << std::endl;

}

Simulation::~Simulation(){
	
}

bool Simulation::analyzeData(){
	/*for(Obstacle obstacle : obstacles){
		if(obstacle.isInMap() != true) eRRor::outasdfasfd
		exit
		;
	}*/
	for(int i(0); i<nbPlayer; ++i){
	
	
		if ((players[i].getCoordinates().x < -200 ) or (200 < players[i].getCoordinates().x)  
				or (players[i].getCoordinates().y < -200 ) or (200 < players[i].getCoordinates().y)){ 	
				
				std::cout << PLAYER_OUT(i+1) << std::endl;
				exit(0);
		} 
	
	}
	
	for(int i(0); i<nbBall; ++i){
	
	
		if ((balls[i].getCoordinates().x < -200 ) or (200 < balls[i].getCoordinates().x)  
				or (balls[i].getCoordinates().y < -200 ) or (200 < balls[i].getCoordinates().y)){ 	
				
				std::cout << BALL_OUT(i+1) << std::endl;
				exit(0);
		} 
	
	}
	
	for(int i(0); i<nbObstacle; ++i){
	

	if (obstacles[i].getCoordinates().x < 0 ) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(obstacles[i].getCoordinates().x) << std::endl;
				exit(0);
			} 
			
		
		if (nbCell < obstacles[i].getCoordinates().x) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(obstacles[i].getCoordinates().x) << std::endl;
				exit(0);
			}
		
		if (obstacles[i].getCoordinates().y < 0 ) { 
			std::cout << OBSTACLE_VALUE_INCORRECT(obstacles[i].getCoordinates().y) << std::endl;
				exit(0);
			}
		
		if (nbCell < obstacles[i].getCoordinates().y){ 	
			std::cout << OBSTACLE_VALUE_INCORRECT(obstacles[i].getCoordinates().y) << std::endl;
				exit(0);
			}
		
		}  
		
	for( int i(0); i<nbObstacle-1; ++i) { 
		for ( int j(i+1); j < nbObstacle; ++j) { 
			
			// if (obstacles[i]==obstacles[j]) { faire une surcharge d'opérateur car commence a faire bcp la 
			if ( (obstacles[i].getCoordinates().x == obstacles[j].getCoordinates().x) and (obstacles[i].getCoordinates().y == obstacles[j].getCoordinates().y) ) {
				std::cout << MULTI_OBSTACLE(obstacles[i].getCoordinates().x, obstacles[i].getCoordinates().y) << std::endl; 
				exit(0);
			}
		}
	}
	
	return false;
}



void Simulation::readNumber(ifstream& file, int& value){
	while(value == -1){
		std::cout << "while loop" << std::endl;
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

//Is there a defined strict format or yolo?
void Simulation::readData(string& fileName){
	/*Tools::Coordinates coos = {3,3};
	Player player(coos, 3,33,3);
	players.push_back(player);*/
	
	
	
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
			players.push_back(player);
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
			obstacles.push_back(obstacle);
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
			balls.push_back(ball);
			i++;
			file.clear();
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Inserted ball : " << i << std::endl;
		}
	} while(i < nbBall);
	
	//return true; //If we get to this line, everything went O.K.
	file.close();
}
