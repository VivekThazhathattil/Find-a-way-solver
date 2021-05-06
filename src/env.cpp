#include "../include/env.h"

Env::Env() {
	resetEnv();
}
Env::~Env() {}

void Env::resetEnv(){
	isVisited.clear();
	dots.clear();
	obstacles.clear();
	srand(time(NULL));
	genGrid();
	genObstacles();
	genDots();
	genStartPos();
}

void Env::genGrid(){
/* gets a random number for m and n */		
	while(1){
		m = rand()%RAND_GRID_LIM + MIN_GRID_M;	
		n = rand()%RAND_GRID_LIM + MIN_GRID_N;

		if ( (m+1)*GRID_SPACING < WINDOW_SIZE_X &&\
			(n+1)*GRID_SPACING < WINDOW_SIZE_Y\
		   )
			break;
	}
}

void Env::genObstacles(){
	int numObstacles = rand()% (MAX_OBSTACLES-MIN_OBSTACLES) + MIN_OBSTACLES;
	for(int i = 0; i < numObstacles; i++){
		Pos pos = getFreeGrid();	
		obstacles.push_back(pos);
	}
}

void Env::genStartPos(){
	startPos = getFreeGrid();		
}

Pos Env::getFreeGrid(){
	while(1){
		bool flag = false;
		Pos pos = {rand()%n, rand()%m};
		for (int j = 0; j < obstacles.size(); j++)
		{
			if(obstacles[j].x == pos.x && obstacles[j].y == pos.y){
				flag = true;
				break;
			}
		}
		if(!flag){
			return pos;
		}
	}
	Pos pos = {-1,-1};
	return pos;
}

int Env::getGridIdFromPos(Pos& pos){
	return pos.x + n*pos.y;
}

Pos Env::getPosFromGridId(int& gid){
	Pos pos = {gid%n, (int((gid-gid%n)/n))};
	return pos;
}

void Env::genDots(){
	for (int i = 0; i < m*n; i++)
	{
		Pos pos = getPosFromGridId(i);
		if(isGridFree(i))
		{ 
			dots.push_back(i);
		}
	}

}

bool Env::isGridFree(int& gid){
	Pos pos = getPosFromGridId(gid);
	bool flag = true;
	for (int j = 0; j < obstacles.size(); j++)
	{
		if(obstacles[j].x == pos.x && obstacles[j].y == pos.y){
			flag = false;
			break;
		}
	}
	return flag;
}
