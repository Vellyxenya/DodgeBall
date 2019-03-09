#include "string"
#include "tools.h"

bool Tools::isTxt(std::string fileName){
	if(fileName.substr(fileName.rfind(".")+1) == "txt")
		return true;
	return false;
};
