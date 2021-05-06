#include <vector>
#include <stdlib.h>
#include <time.h>
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
		std::vector<bool> isVisited;

		Env();
		~Env();
		void resetEnv();
		bool isGridFree(int& gid); // check if an obstacle is present in the grid corresponding to the gid
		int getGridIdFromPos(Pos& pos);
		Pos getPosFromGridId(int& gid);
};
