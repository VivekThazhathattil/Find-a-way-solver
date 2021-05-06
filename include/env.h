#include <vector>
#include <stdlib.h>
#include <time.h>
#include "consts.h"
#include "position.h"

#define IX(i,j) i+

Class Env{
	private:
		int m, int n;
		vector<Pos> obstacles;
		vector<bool> isVisited;
		void genObstacles();
		void genStartPos();
		void genGrid();

	public:
		int idx(int& i, int& j, int& maxJ);
		Env();
		~Env();
};
