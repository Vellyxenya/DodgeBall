#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "actor.h"
#include "define.h"
#include "player.h"
#include "ball.h"
#include "obstacle.h"
#include "error.h"

class Map{
	public:
		Map(int nbCells);
		~Map();
		
		//Player-Player, Player-Ball, Ball-Ball
		bool isColliding(Actor actor1, Actor actor2) const;
		bool collisionWithObstacle(Actor actor, Obstacle obstacle);
		Coordinates toSimulationCoos(Coordinates coos, double side);
		
		void detectCollisions();
		void playerVsPlayer() const;
		void playerVsBall() const;
		void ballVsBall() const;
		void playerVsObstacle();
		void ballVsObstacle();
		
		std::vector<Player>& getPlayers();
		std::vector<Ball>& getBalls();
		std::vector<Obstacle>& getObstacles();
		
	private:
		unsigned int nbCell;
		double ML;
		double MJ;
		
		std::vector<Player> players;	
		std::vector<Ball> balls;
		std::vector<Obstacle> obstacles;
	
};

#endif
