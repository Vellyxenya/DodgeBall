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

enum ActorType{
	PLAYER,
	OBSTACLE,
	BALL
};

class Map{
	public:
		Map(int nbCells);
		~Map();
		
		//Player-Player, Player-Ball, Ball-Ball
		bool isColliding(Actor actor1, Actor actor2) const;
		bool collisionWithObstacle(Actor actor, Obstacle obstacle);
		Coordinates toSimulationCoos(Coordinates coos, double side);
		
		void analyzeActors(ActorType actor, int& numberOfActors);
		void analyzeData();
		
		void detectCollisions();
		void playerVsPlayer() const;
		void playerVsBall() const;
		void ballVsBall() const;
		void playerVsObstacle();
		void ballVsObstacle();
		
		std::vector<Player>& getPlayers();
		std::vector<Ball>& getBalls();
		std::vector<Obstacle>& getObstacles();
		
		int getNbPlayer() const;
		int getNbObstacle() const;
		int getNbBall() const;
		
		void setNbPlayer(int nbPlayerIn);
		void setNbObstacle(int nbObstacleIn);
		void setNbBall(int nbBallIn);
		
	private:
		unsigned int nbCell;
		double ML;
		double MJ;
		
		int nbPlayer;
		int nbObstacle;
		int nbBall;
		
		std::vector<Player> players;	
		std::vector<Ball> balls;
		std::vector<Obstacle> obstacles;
	
};

#endif
