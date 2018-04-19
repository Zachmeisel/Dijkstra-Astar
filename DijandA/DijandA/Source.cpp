#include "Source.h"
#include "Grid.h"
#include "dijkstra.h"
#include "AStar.h"
#include "Nodes.h"
#include <iostream>
#include <time.h>

Source::Source()
{
}


Source::~Source()
{
}

void main()
{
	Grid * g = new Grid;
	dijkstra * d = new dijkstra;
	AStar * a = new AStar;
	clock_t t1, t2;
	Nodes* graph[10][10];

	g->creategrid(graph);
	t1 = clock();

	d->shortestPath(graph);
	t2 = clock();

	float diff((float)t2 - (float)t1);
	std::cout << "Time it takes for Dijkstra to run " << diff << endl;
	std::cout << std::endl;
	pair<int, int> src = make_pair(0, 0);

	pair<int, int> dest = make_pair(6, 7);
	t1 = clock();
	a->aStarSearch(graph, src, dest);
	t2 = clock();
	float diff2((float)t2 - (float)t1);
	std::cout <<"Time it takes for A-Star to run " << diff2 << endl;

	cin.get();
}
