/**
 * Last modified on : 11/03/2019
 * Comments : Mode selection based on command line options.
 */

#include <iostream>
#include <cstring>

#include "simulation.h"
#include "tools.h"

#define ONE_ARG 1
#define TWO_ARG 2
#define THREE_ARG 3
#define FOUR_ARG 4

using namespace std;

bool chooseMode(int argc, char* argv[], Mode& mode);

int main(int argc, char* argv[]){
	
	Mode mode;
	
	if(!chooseMode(argc, argv, mode)) {
		cerr << "Commande incorrecte" << endl;
		exit(0);
	}

	Simulation simulation(mode, argv[2]);

	return 0;	
}

bool chooseMode(int argc, char* argv[], Mode& mode){
	switch(argc){
		case ONE_ARG:
			mode = Normal;
			break;
			
		case TWO_ARG:
			if (Tools::isTxtFile(argv[1])) mode = Normal;
			else return false;
			break;
			
		case THREE_ARG:
			if (argv[1] == string("Error") &&
				Tools::isTxtFile(argv[2])) {
				mode = Error;
			} else return false;
			break;
			
		case FOUR_ARG:
			if (argv[1] == string("Step") && Tools::isTxtFile(argv[2])
				&& Tools::isTxtFile(argv[3])) {
				mode = Step;
			} else return false;
			break;
			
		default:
			return false;
	}
	return true;
}
