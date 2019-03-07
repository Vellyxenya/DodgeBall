#include <iostream>
#include <fstream>
#include "simulation.h"

using namespace std;

Simulation::Simulation(Mode mode, string fileName){
	std::cout << "Using mode : " << mode << std::endl;
	readData(fileName);
	//analyzeData();
	//analze txt
	
}

Simulation::~Simulation(){
	
}


/*analyzeData(vector<Obstacle> obstacles){
	for(Obstacle obstacle : obstacles){
		if(obstacle.isInMap() != true) eRRor::outasdfasfd
		exit
		;
	}
}*/

//Is there a defined strict format or yolo?
bool Simulation::readData(string& fileName){
	//Cin Junk (# comments) and get rid of it
	ifstream file;
	file.open(fileName);
	
	string input;
	file >> input;
	//cout << input << endl;
	
	
	file.close();
	
	int nbCell; //declare as parameter instead, or find solution
	//define nbCell as a global variable? static? with #define? MACRO?
	cin >> nbCell;
	
	int nbPlayer;
	cin >> nbPlayer;
	
	//cin each player, verify validity of data
	
	int nbObstacle; //Can we put an s at the end of obstacle?
	cin >> nbObstacle;
	
	//cin each obstacle, make tests use tools functions to test
	
	int nbBall;
	cin >> nbBall;
	
	//cin each ball, make tests etc...
	
	return true; //If we get to this line, everything went O.K.
}
