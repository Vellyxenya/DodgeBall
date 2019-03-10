#include "map.h"

using namespace std;

Map::Map(int nbCell) : 	nbCell(nbCell) {
	MJ = COEF_MARGE_JEU * (SIDE/nbCell);
	ML = COEF_MARGE_JEU/2 * (SIDE/nbCell);
}

void Map::analyzeActors(ActorType actorType, int& numberOfActors){ 
	
	for (int i(0); i < numberOfActors; ++i) {
		switch(actorType) { 
			case PLAYER :
				players[i].analyzePosition(i); //i+1 est faux
				break;
			case OBSTACLE :
				obstacles[i].analyzePosition(nbCell);
				break;
			case BALL :
				balls[i].analyzePosition(i); //i+1 est faux
				break; 
		} 
	}
	
	if (actorType == OBSTACLE) { 
		for(int i(0); i < numberOfActors; ++i) { //why -1?
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
	
	std::cout << "No collisions detected" << std::endl;
}

void Map::playerVsPlayer() const {
	for(size_t i(0); i <= players.size(); ++i){
		for(size_t j(i+1); j < players.size(); ++j){
			if(isColliding(players[i], players[j])) {
				std::cout << PLAYER_COLLISION(i+1, j+1) << std::endl;
				exit(0);
			}
		}
	}
}

void Map::playerVsBall() const {
	for(size_t i(0); i < players.size(); ++i){
		for(size_t j(0); j < balls.size(); ++j){
			if(isColliding(players[i], balls[j])) {
				std::cout << "NOT YET AVAILABLE" << std::endl;
				exit(0);
			}
		}
	}
}

void Map::ballVsBall() const {
	for(size_t i(0); i < players.size(); ++i){
		for(size_t j(i+1); j < players.size(); ++j){
			if(isColliding(players[i], players[j])) {
				std::cout << "NOT YET AVAILABLE" << std::endl;
				exit(0);
			}
		}
	}
}

void Map::playerVsObstacle() {
	for(size_t i(0); i < players.size(); ++i){
		for(size_t j(0); j < obstacles.size(); ++j){
			if(collisionWithObstacle(players[i], obstacles[j])) {
				std::cout << COLL_OBST_PLAYER(j+1, i+1) << std::endl;
				exit(0);
			}
		}
	}
}

void Map::ballVsObstacle() {
	for(size_t i(0); i < balls.size(); ++i){
		for(size_t j(0); j < obstacles.size(); ++j){
			if(collisionWithObstacle(balls[i], obstacles[j])) {
				std::cout << COLL_BALL_OBSTACLE(i+1) << std::endl;
				exit(0);
			}
		}
	}
}

bool Map::collisionWithObstacle(Actor actor, Obstacle obstacle) {
	Coordinates actorCoos = actor.getCoordinates();
	Coordinates obsCoos = toSimulationCoos( obstacle.getCoordinates(),
											obstacle.getSize());
	double squareHalfSide = obstacle.getSize() + actor.getSize();
	double circleRadius = sqrt(2)*obstacle.getSize() + actor.getSize();
	Square square = {obsCoos, squareHalfSide};
	Circle circle = {obsCoos, circleRadius};
	if(Tools::isInSquare(actorCoos, square) &&
		Tools::isInCircle(actorCoos, circle)){
		return true;
	}
	return false;
}

Coordinates Map::toSimulationCoos(Coordinates coos, double halfSide){
	Coordinates simulationCoos =
		{coos.y * 2 * halfSide - halfSide - DIM_MAX,
		coos.x * 2 * halfSide - halfSide - DIM_MAX};
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
