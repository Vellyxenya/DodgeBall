#include "map.h"

using namespace std;

#include <cmath>

Map::Map(int nbCell) : 	nbCell(nbCell) {
	MJ = COEF_MARGE_JEU * (SIDE/nbCell);
	ML = COEF_MARGE_JEU/2 * (SIDE/nbCell);
}

Map::~Map(){
	
}

void Map::analyzeActors(ActorType actorType, int& numberOfActors){ 
	
	for (int i(0); i < numberOfActors; ++i) {
		switch(actorType) { 
			case PLAYER :
				players[i].analyzePosition(i);
				break;
			case OBSTACLE :
				obstacles[i].analyzePosition(nbCell);
				break;
			case BALL :
				balls[i].analyzePosition(i);
				break; 
		} 
	}
	
	if (actorType == OBSTACLE) { 
		for(int i(0); i < numberOfActors - 1; ++i) {
			for (int j(i+1); j < numberOfActors; ++j){ 
				obstacles[i].analyzeDuplication(obstacles[j]);  
			}
		} 
	}
}

void Map::analyzeData(){
	analyzeActors(PLAYER, nbPlayer); 
	analyzeActors(OBSTACLE, nbObstacle); 
	analyzeActors(BALL, nbBall); 
	cout << "Data analyzed" << endl;
}

void Map::detectCollisions() {
	playerVsPlayer();
	playerVsBall();
	ballVsBall();
	playerVsObstacle();
	ballVsObstacle();
	
	cout << "No collisions detected" << endl;
}

void Map::playerVsPlayer() const {
	for(size_t i(0); i <= players.size(); ++i){
		for(size_t j(i+1); j < players.size(); ++j){
			if(isColliding(players[i], players[j])) {
				cout << PLAYER_COLLISION(i+1, j+1) << endl;
				exit(0);
			}
		}
	}
}

void Map::playerVsBall() const {
	for(size_t i(0); i < players.size(); ++i){
		for(size_t j(0); j < balls.size(); ++j){
			if(isColliding(players[i], balls[j])) {
				cout << PLAYER_BALL_COLLISION(i+1, j+1) << endl;
				exit(0);
			}
		}
	}
}

void Map::ballVsBall() const {
	for(size_t i(0); i < balls.size(); ++i){
		for(size_t j(i+1); j < balls.size(); ++j){
			if(isColliding(balls[i], balls[j])) {
				cout << BALL_COLLISION(i+1, j+1) << endl;
				exit(0);
			}
		}
	}
}

void Map::playerVsObstacle() {
	for(size_t i(0); i < players.size(); ++i){
		for(size_t j(0); j < obstacles.size(); ++j){
			if(collisionWithObstacle(players[i], obstacles[j])) {
				cout << COLL_OBST_PLAYER(j+1, i+1) << endl;
				exit(0);
			}
		}
	}
}

void Map::ballVsObstacle() {
	for(size_t i(0); i < balls.size(); ++i){
		for(size_t j(0); j < obstacles.size(); ++j){
			if(collisionWithObstacle(balls[i], obstacles[j])) {
				cout << COLL_BALL_OBSTACLE(i+1) << endl;
				exit(0);
			}
		}
	}
}

bool Map::collisionWithObstacle(Actor actor, Obstacle obstacle) {
	Coordinates actorCoos = actor.getCoordinates();
	Coordinates obsCoos = toSimulationCoos( obstacle.getCoordinates(),
											obstacle.getSize());
	double hs = obstacle.getSize() + actor.getSize(); //HalfSide of square
	//double circleRadius = sqrt(2)*obstacle.getSize() + actor.getSize();
	double r = actor.getSize();
	double circleRadius = sqrt(hs*hs+(r+hs)*(r+hs));
	Square square = {obsCoos, hs};
	Circle circle = {obsCoos, circleRadius};
	Coordinates shift1 = {obstacle.getSize(), obstacle.getSize()};
	Coordinates shift2 = {obstacle.getSize(), -obstacle.getSize()};
	Circle circle1 = {obsCoos+shift1, actor.getSize()};
	Circle circle2 = {obsCoos+shift2, actor.getSize()};
	Circle circle3 = {obsCoos-shift1, actor.getSize()};
	Circle circle4 = {obsCoos-shift2, actor.getSize()};
	if((Tools::isInSquare(actorCoos, square) &&
		Tools::isInCircle(actorCoos, circle)) ||
		Tools::isInCircle(actorCoos, circle1) ||
		Tools::isInCircle(actorCoos, circle2) ||
		Tools::isInCircle(actorCoos, circle3) ||
		Tools::isInCircle(actorCoos, circle4)) {
		return true;
	}
	return false;
}

Coordinates Map::toSimulationCoos(Coordinates coos, double halfSide){
	Coordinates simulationCoos =
		{coos.y * 2 * halfSide + halfSide - DIM_MAX,
		-(coos.x * 2 * halfSide + halfSide - DIM_MAX)};
	return simulationCoos;
}

//Player-Player, Player-Ball, Ball-Ball
bool Map::isColliding(Actor actor1, Actor actor2) const{
	Coordinates coos1 = actor1.getCoordinates();
	Coordinates coos2 = actor2.getCoordinates();
	double size1 = actor1.getSize();
	double size2 = actor2.getSize();
	
	double distance = Tools::distance(coos1, coos2) ;
	if (distance < (size1 + size2 + ML)) {
		return true;
	}
	return false;
}

vector<Player>& Map::getPlayers(){
	return players;
}

vector<Ball>& Map::getBalls(){
	return balls;
}

vector<Obstacle>& Map::getObstacles(){
	return obstacles;
}

int Map::getNbPlayer() const{
	return nbPlayer;
}
int Map::getNbObstacle() const{
	return nbObstacle;
}
int Map::getNbBall() const{
	return nbBall;
}
void Map::setNbPlayer(int nbPlayerIn){
	nbPlayer = nbPlayerIn;
}
void Map::setNbObstacle(int nbObstacleIn){
	nbObstacle = nbObstacleIn;
}
void Map::setNbBall(int nbBallIn){
	nbBall = nbBallIn;
}
