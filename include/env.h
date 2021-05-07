#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "consts.h"
#include "position.h"

class Env{
	private:
		void genObstacles();
		void genStartPos();
		void genGrid();
		void genDots();
		Pos getFreeGrid();
	public:
		int m;
		int n;
		std::vector<Pos> obstacles;
		std::vector<int> dots; // gid of all dots including grey and pink dots 
		Pos startPos;
		std::vector<std::vector<bool>> adjMat;
		std::vector<int> path;

		Env();
		~Env();
		void resetEnv();
		bool isGridFree(int& gid); // check if an obstacle is present in the grid corresponding to the gid
		int getGridIdFromPos(Pos& pos);
		Pos getPosFromGridId(int& gid);
		void genAdjacencyMatrix();
		bool getHamiltonianPath();
		bool hamiltonianCycleUtil(int pos);
		void printSolution_stub();
		int getNextGidForDots(int s);
		void initializePath();
		bool isSafe(int v, int pos);
};
