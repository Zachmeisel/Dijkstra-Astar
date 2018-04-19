#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include "Nodes.h"
#include "Grid.h"

class dijkstra
{
public:
	dijkstra();
	~dijkstra();

	void shortestPath(Nodes*[][10]);
};

