#include "dijkstra.h"

//Make parents for the path from the destination to the source
std::vector<std::pair<int, int> > parent;
int parent1[10][10];
int parent2[10][10];
dijkstra::dijkstra()
{
}


dijkstra::~dijkstra()
{
}



void dijkstra::shortestPath(Nodes* graph[][10])
{
	graph[6][7]->end = true;
	int i, j;
	int dist[10][10];
	bool intree[10][10];
	int vert1, vert2;
	int nex1, nex2;
	int weight;
	int dist2;

	//Setup all of the arrays and information
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			dist[i][j] = INT_MAX;
			intree[i][j] = false;
			parent1[i][j] = -1;
			parent2[i][j] = -1;
			parent.push_back(std::make_pair(-1,-1));
		}
	}
	int source1 = 0;
	int source2 = 0;
	dist[source1][source2] = 0;
	vert1 = 0;
	vert2 = 0;


	while (intree[vert1][vert2] == false) {
		//Run this code as long as the vertex is open
		if (graph[vert1][vert2]->open != false)
		{

			intree[vert1][vert2] = true;
			//iterate through all of the adjacent vertices
			for (i = 0; i < graph[vert1][vert2]->adjacent.size(); i++) {
				//If the adjacent node is not set to blank
				//Set up the node and the weight in the parent arrays
				if (graph[vert1][vert2]->adjacent[i].second != -1)
				{

				nex1 = graph[vert1][vert2]->adjacent[i].first->num1;
				nex2 = graph[vert1][vert2]->adjacent[i].first->num2;
				weight = graph[vert1][vert2]->adjacent[i].second;
				if (dist[nex1][nex2] > (dist[vert1][vert2] + weight)) {
					dist[nex1][nex2] = dist[vert1][vert2] + weight;
					parent1[nex1][nex2] = vert1;
					parent2[nex1][nex2] = vert2;
					parent.push_back(std::make_pair(vert1, vert2));
				}
				}
				else
				{
					nex1 = graph[vert1][vert2]->adjacent[i].first->num1;
					nex2 = graph[vert1][vert2]->adjacent[i].first->num2;
					weight = graph[vert1][vert2]->adjacent[i].second;
				}
			}
		}
			vert1 = 0;
			vert2 = 0;
			dist2 = 1000;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if ((intree[i][j] == false) && (dist2 > dist[i][j]) && (graph[i][j]->open != false)) {
						dist2 = dist[i][j];
						vert1 = i;
						vert2 = j;
					}
				}
			}
	}
	int index1 = 1000;
	int index2 = 1000;
	int next1 =6;
	int next2 =7;
	//The weight is calculated for each node from the starting node 
	//Print a graph of the path for verifying it is correct and matching to AStar
			std::cout << std::endl << "The weight is " << dist[6][7] << std::endl;
			std::cout << "The path is " << std::endl;
			graph[6][7]->path = true;
			while (index1 != source1-1 && index2 != source2-1 )
			{
				index1 = parent1[next1][next2];
				index2 = parent2[next1][next2];
				if (index1 != -1 && index2 != -1)
				{
					next1 = graph[index1][index2]->num1;
					next2 = graph[index1][index2]->num2;
					graph[index1][index2]->path = true;
				}
			}
			for (int q = 0; q < 10; q++)
			{
				for (int q1 = 0; q1 < 10; q1++)
				{

					if (graph[q][q1]->open == false)
					{
						std::cout << " " << " ";
					}
					else if (graph[q][q1]->path == true)
					{
						std::cout << "O" << " ";
					}
					else
					{
						std::cout << "X" << " ";
					}
					
				}
				std::cout << std::endl;
			}
	
}