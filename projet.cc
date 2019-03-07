/**
 * Last modified on : 02/03/2019
 * Comments : Mode selection based on input options.
 */

#include <iostream>
#include <cstring>
#include <string>

#include "simulation.h"
#include "tools.h"

using namespace std;

bool chooseMode(int argc, char* argv[], Mode& mode);

int main(int argc, char* argv[]){
	
	Mode mode;
	
	chooseMode(argc, argv, mode);

	Simulation simulation(mode, argv[2]); //runs simulation

	return 0;	
}

bool chooseMode(int argc, char* argv[], Mode& mode){
	switch(argc){
		case 1:
			mode = Normal;
			break;
			
		case 2:
			if (Tools::isTxt(argv[1]))	mode = Normal;
			else return false;
			break;
			
		case 3:
			if(argv[1] == string("Error") && Tools::isTxt(argv[2])){
				mode = Error;
			}
			else return false;
			break;
			
		case 4:
			if(argv[1] == string("Step")
				&& Tools::isTxt(argv[2]) && Tools::isTxt(argv[3])){
				mode = Step;
			}
			else return false;
			break;
			
		default:
			cout << "Incorrect number of parameters" << endl;
			return false;
	}
}