#ifndef MAP_H
#define MAP_H

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

enum CollisionType{
	PLAYER_VS_PLAYER,
	BALL_VS_BALL,
	PLAYER_VS_BALL,
	PLAYER_VS_OBSTACLE,
	BALL_VS_OBSTACLE
};

class Map{
	public:
		Map(int nbCells);
		~Map();
		
		void analyzeBounds();		
		void detectCollisions();
		
		std::vector<Player*>& getPlayers();
		std::vector<Ball*>& getBalls();
		std::vector<Obstacle*>& getObstacles();
		
		unsigned int getNbCell() const;
		unsigned int getNbPlayer() const;
		unsigned int getNbObstacle() const;
		unsigned int getNbBall() const;

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
	   
		//Player-Player, Player-Ball, Ball-Ball
		bool isColliding(Actor* actor1, Actor* actor2) const;
		
		//Player-Obstacle, Ball-Obstacle
		bool collisionWithObstacle(Actor* actor, Obstacle* obstacle);
		
		//Transforms Cell coordinates to Map Coordinates
		Coordinates toSimulationCoos(const Coordinates& coos,
									 double side);
		
		void analyzeActors(const ActorType& actor, int& numberOfActors);
		
		template<typename T, typename S>
		void actorVsActor(const std::vector<T*>& actors1,
						  const std::vector<S*>& actors2, 
						  const CollisionType& collsionType);
		
		template<typename T>
		void actorVsObstacle(const std::vector<T*>& actors,
							 const CollisionType& collisionType);
							 
		void obstacleVsObstacle(const std::vector<Obstacle*>&
								obstacles);
};

#endif
