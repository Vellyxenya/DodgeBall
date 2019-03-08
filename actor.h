#pragma once
#include "tools.h"

class Actor{
	public:
		Actor();
		Actor(Tools::Coordinates& inCoos, unsigned int size);
		~Actor();
		
		Tools::Coordinates getCoordinates() const{
			return coos;
		}
		
		unsigned int getSize() const{
			return size;
		}
		
		void display(int&);
		
	protected:
		Tools::Coordinates coos;
		unsigned int const size; //May be the radius(for player/ball) or half-side(for obstacle)
		//Mettre const sur size?
};
