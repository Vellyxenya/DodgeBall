#include <iostream>

#include "map.h"

#define FACTOR_TWO 2

using namespace std;

Map::Map(int nbCell) : 	nbCell(nbCell) {
	MJ = COEF_MARGE_JEU * (SIDE/nbCell);
	ML = COEF_MARGE_JEU/FACTOR_TWO * (SIDE/nbCell);
	
	minDimensions = {-DIM_MAX, -DIM_MAX};
	maxDimensions = {DIM_MAX, DIM_MAX};
}

Map::~Map(){
	for (Actor* actor : players) delete actor;
	for (Actor* actor : balls) delete actor;
	for (Obstacle* obstacle : obstacles) delete obstacle;
	players.clear();
	balls.clear();
	obstacles.clear();
}

void Map::analyzeActors(const ActorType& actorType,
						int& numberOfActors) {
							
	for (int i(0); i < numberOfActors; ++i) {
		switch(actorType) { 
			case PLAYER :
				players[i]->analyzePosition(i, minDimensions,
											maxDimensions);
				break;
			case OBSTACLE :
				obstacles[i]->analyzePosition(nbCell);
				break;
			case BALL :
				balls[i]->analyzePosition(i, minDimensions,
										  maxDimensions);
				break;
		} 
	}
}

void Map::analyzeBounds(){
	analyzeActors(PLAYER, nbPlayer); 
	analyzeActors(OBSTACLE, nbObstacle); 
	analyzeActors(BALL, nbBall);
}

void Map::detectCollisions() {
	actorVsActor(players, players, PLAYER_VS_PLAYER);
	actorVsActor(balls, balls, BALL_VS_BALL);
	actorVsActor(players, balls, PLAYER_VS_BALL);
	actorVsObstacle(players, PLAYER_VS_OBSTACLE);
	actorVsObstacle(balls, BALL_VS_OBSTACLE);
	obstacleVsObstacle(obstacles);
}

void Map::obstacleVsObstacle(const vector<Obstacle*>& obstacles) {
	for(size_t i(0); i < obstacles.size() -1; ++i) {
		for (size_t j(i+1); j < obstacles.size(); ++j){ 
			obstacles[i]->analyzeDuplication(obstacles[j]);  
		}
	}
}

template<typename T, typename S>
void Map::actorVsActor(const vector<T*>& actors1,
					   const vector<S*>& actors2,
					   const CollisionType& collisionType) {
	for(size_t i(0); i < actors1.size(); ++i){
		int init;
		if(typeid(T) == typeid(S)) init = i+1;
		else init = 0;
		for(size_t j(init); j < actors2.size(); ++j){
			if(isColliding(actors1[i], actors2[j])) {
				switch(collisionType) {
					case PLAYER_VS_PLAYER :
						cerr << PLAYER_COLLISION(i+1, j+1) << endl;
						break;
					case BALL_VS_BALL :
						cerr << BALL_COLLISION(i+1, j+1) << endl;
						break;
					case PLAYER_VS_BALL :
						cerr << PLAYER_BALL_COLLISION(i+1, j+1) << endl;
						break;
					default :
						break;
				}
				exit(0);
			}
		}
	}
}

template<typename T>
void Map::actorVsObstacle(const vector<T*>& actors,
						  const CollisionType& collisionType) {
							  
	for(size_t i(0); i < actors.size(); ++i){
		for(size_t j(0); j < obstacles.size(); ++j){
			if(collisionWithObstacle(actors[i], obstacles[j])) {
				switch(collisionType){
					case PLAYER_VS_OBSTACLE :
						cerr << COLL_OBST_PLAYER(j+1, i+1) << endl;
						break;
					case BALL_VS_OBSTACLE:
						cerr << COLL_BALL_OBSTACLE(i+1) << endl;
						break;
					default :
						break;
				}
				exit(0);
			}
		}
	}
}

bool Map::collisionWithObstacle(Actor* actor, Obstacle* obstacle) {
	Coordinates actorCoos = actor->getCoordinates();
	Coordinates obsCoos = toSimulationCoos( obstacle->getCoordinates(),
											obstacle->getSize());
											
	double halfSide = obstacle->getSize() + actor->getSize();
	double r = actor->getSize();
	double circleRadius = Tools::getHypothenus(halfSide, r+halfSide);
	double obSize = obstacle->getSize();
	
	Square square = {obsCoos, halfSide};
	Circle mainCircle = {obsCoos, circleRadius};
	Coordinates shift1 = {obSize, obSize};
	Coordinates shift2 = {obSize, -obSize};
	
	Circle circle1 = {obsCoos+shift1, actor->getSize()};
	Circle circle2 = {obsCoos+shift2, actor->getSize()};
	Circle circle3 = {obsCoos-shift1, actor->getSize()};
	Circle circle4 = {obsCoos-shift2, actor->getSize()};
	
	if((Tools::isInSquare(actorCoos, square) &&
		Tools::isInCircle(actorCoos, mainCircle)) ||
		Tools::isInCircle(actorCoos, circle1) ||
		Tools::isInCircle(actorCoos, circle2) ||
		Tools::isInCircle(actorCoos, circle3) ||
		Tools::isInCircle(actorCoos, circle4)) return true;
	return false;
}

Coordinates Map::toSimulationCoos(const Coordinates& coos,
								  double halfSide) {
									  
	Coordinates simulationCoos =
		{coos.y * FACTOR_TWO * halfSide + halfSide - DIM_MAX,
		-(coos.x * FACTOR_TWO * halfSide + halfSide - DIM_MAX)};
	return simulationCoos;
}

bool Map::isColliding(Actor* actor1, Actor* actor2) const{
	Coordinates coos1 = actor1->getCoordinates();
	Coordinates coos2 = actor2->getCoordinates();
	double size1 = actor1->getSize();
	double size2 = actor2->getSize();
	
	double distance = Tools::distance(coos1, coos2) ;
	if (distance < (size1 + size2 + ML)) return true;
	return false;
}

vector<Player*>& Map::getPlayers(){
	return players;
}

vector<Ball*>& Map::getBalls(){
	return balls;
}

vector<Obstacle*>& Map::getObstacles(){
	return obstacles;
}

unsigned int Map::getNbCell() const{
	return nbCell;
}

unsigned int Map::getNbPlayer() const{
	return nbPlayer;
}

unsigned int Map::getNbObstacle() const{
	return nbObstacle;
}

unsigned int Map::getNbBall() const{
	return nbBall;
}

bool Map::setNbPlayer(int nbPlayerIn){
	if(nbPlayerIn >= 0) {
		nbPlayer = nbPlayerIn;
		return true;
	}
	return false;
}

bool Map::setNbObstacle(int nbObstacleIn){
	if(nbObstacleIn >= 0) {
		nbObstacle = nbObstacleIn;
		return true;
	}
	return false;
}

bool Map::setNbBall(int nbBallIn){
	if(nbBallIn >= 0) {
		nbBall = nbBallIn;
		return true;
	}
	return false;
}
