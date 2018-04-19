#pragma once

#include <stack>
#include <string>
#include <list>
#include <set>
#include "Nodes.h"
using namespace std;
class AStar
{
public:
	AStar();
	~AStar();

	

#define ROW 9
#define COL 10

	typedef pair<int, int> Pair;

	typedef pair<double, pair<int, int>> pPair;

	void aStarSearch(Nodes *[][10], Pair, Pair);
};

