#include "../include/env.h"

Env::Env() { 
	genGrid();
	genObstacles();
	genStartPos();
}
Env::~Env() {}

int Env::idx(int& i, int& j){
	return (j + maxJ * i);
}
