#include "../include/env.h"

Env::Env() {
	resetEnv();
}
Env::~Env() {}

void Env::resetEnv(){
	path.clear();
	dots.clear();
	obstacles.clear();
	adjMat.clear();

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
//		m = 4;
//		n = 4;

		if ( (m+1)*GRID_SPACING < WINDOW_SIZE_X &&\
			(n+1)*GRID_SPACING < WINDOW_SIZE_Y\
		   )
			break;
	}
}

void Env::genObstacles(){
	int numObstacles = rand()% (MAX_OBSTACLES-MIN_OBSTACLES) + MIN_OBSTACLES;
//	int numObstacles = 1;
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

void Env::genAdjacencyMatrix(){
	for (int i = 0; i < m*n; i++){
		adjMat.push_back(std::vector<bool>());
		for (int j = 0; j < m*n; j++){
			adjMat[i].push_back(false);
		}
	}

	for (int gid = 0; gid < dots.size(); gid++){
		Pos pos = getPosFromGridId(dots[gid]);
		Pos nextPos;
		int nextGid;

		/* Up */
		if(pos.y > 0){
			nextPos = {pos.x, pos.y-1};
			nextGid = getGridIdFromPos(nextPos);
			if(isGridFree(nextGid))
				adjMat[dots[gid]][nextGid] = true;
		}
		/* Down */
		if(pos.y < m-1){
			nextPos = {pos.x, pos.y+1};
			nextGid = getGridIdFromPos(nextPos);
			if(isGridFree(nextGid))
				adjMat[dots[gid]][nextGid] = true;
		}
		/* Left */
		if(pos.x > 0){
			nextPos = {pos.x-1, pos.y};
			nextGid = getGridIdFromPos(nextPos);
			if(isGridFree(nextGid))
				adjMat[dots[gid]][nextGid] = true;
		}
		/* Right */
		if(pos.x < n-1){
			nextPos = {pos.x+1, pos.y};
			nextGid = getGridIdFromPos(nextPos);
			if(isGridFree(nextGid))
				adjMat[dots[gid]][nextGid] = true;
		}
	}
}

int Env::getNextGidForDots(int s){
	for(int i = 0; i < dots.size()-1; i++)
		if(s == dots[i])
			return dots[i+1];
	return dots[0];
}

bool Env::getHamiltonianPath(){
	genAdjacencyMatrix();
	initializePath();
	path[0] = getGridIdFromPos(startPos);
	if (hamiltonianCycleUtil(1) == false ){
		std::cout << "\nSolution does not exist\n";
		std::cout << "Adj Mat:\n";
		for (int i = 0; i < m*n; i++){
			for (int j = 0; j < m*n; j++){
				if(adjMat[i][j])
					std::cout << "1 ";
				else
					std::cout << "0 ";
			}
			std::cout << "\n";
		}
		std::cout << "obstacle position: (" << obstacles[0].x << "," << obstacles[0].y << ")\n";
		std::cout << " Path:\n";
		for(int i = 0; i < path.size(); i++)
			std::cout << path[i] << " ";
		std::cout << "\n";
		std::cout << " startPos: (" << startPos.x << "," << startPos.y << ")\n";
//		exit(0);
		return false;
		}
	printSolution_stub();
	return true;
}

void Env::printSolution_stub() { 
	std::cout << "Solution Exists:\n";
	for (int i = 0; i < m*n-obstacles.size(); i++) 
		std::cout << path[i] << " "; 
	std::cout << std::endl;
} 

bool Env::hamiltonianCycleUtil(int pos){
	if (pos == m*n - obstacles.size())
	        return true;

	for (int v = 1; v < m*n; v++){
	    if (isSafe(v, pos)){
	        path[pos] = v;
	        if (hamiltonianCycleUtil(pos + 1) == true)
	            return true;
	
	        path[pos] = -1;
	    }
	}
	return false;
}

bool Env::isSafe(int v, int pos) { 
	if (!adjMat [path[pos - 1]][v]) 
		return false; 
	
	for (int i = 0; i < pos; i++) 
		if (path[i] == v) 
			return false; 
	return true; 
} 

void Env::initializePath(){
	for(int i = 0; i < dots.size(); i++){
		path.push_back(-1);
	}
}
