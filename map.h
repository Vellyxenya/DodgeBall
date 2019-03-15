#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

#include "define.h"
#include "error.h"
#include "actor.h"
#include "player.h"
#include "ball.h"
#include "obstacle.h"

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
		bool isColliding(Actor* actor1, Actor* actor2) const;
		//Player-Obstacle, Ball-Obstacle
		bool collisionWithObstacle(Actor* actor, Obstacle* obstacle);
		//Transforms Cell coordinates to Map Coordinates
		Coordinates toSimulationCoos(Coordinates coos, double side);
		
		void analyzeActors(ActorType actor, int& numberOfActors);
		void analyzeBounds();
		
		void detectCollisions();
		void playerVsPlayer() const;
		void playerVsBall() const;
		void ballVsBall() const;
		void playerVsObstacle();
		void ballVsObstacle();
		
		std::vector<Player*>& getPlayers();
		std::vector<Ball*>& getBalls();
		std::vector<Obstacle*>& getObstacles();
		
		int getNbCell() const;
		int getNbPlayer() const;
		int getNbObstacle() const;
		int getNbBall() const;

		bool setNbPlayer(int nbPlayerIn);
		bool setNbObstacle(int nbObstacleIn);
		bool setNbBall(int nbBallIn);
		
	private:
		unsigned int nbCell;
		double ML;
		double MJ;
		
		int nbPlayer;
		int nbObstacle;
		int nbBall;
		
		std::vector<Player*> players;	
		std::vector<Ball*> balls;
		std::vector<Obstacle*> obstacles;
		
		Coordinates minDimensions;
		Coordinates maxDimensions;
};

#endif
