#include "Grid.h"



Grid::Grid()
{
}


Grid::~Grid()
{
}

void Grid::creategrid(Nodes * graph[10][10])
{
	int set_Num = 0;
	Nodes * Blank = new Nodes;
	//For all the weights on the edges
	int setup[360] = { 3,9,10,7,1,2,12,7,8,9,6,8,8,5,9,6,12,3,8,5,1,2,3,3,2,12,12,9,7,4,8,5,2,12,6,8,10,10,9,10,6,3,7,4,4,5,11,9,2,12,6,4,4,7,9,4,7,
						5,7,1,5,5,9,8,8,1,4,10,7,11,5,6,3,1,12,6,11,3,9,8,12,11,3,1,2,2,10,6,2,9,10,9,2,1,8,3,7,8,3,3,9,	10,	12,	10,	10,3,1,11,6,2,10,
						10,5,3,12,9,4,9,9,1,5,10,12,10,7,12,6,5,6,1,8,3,5,12,2,1,2,6,10,5,9,10,1,10,11,6,2,9,6,3,9,9,12,10,3,12,2,7,11,10,8,12,10,4,12,7,8,11,7,4,4,5,2,7,11,6,6,11,6,8,
						3,9,10,2,1,2,12,2,8,1,6,8,1,5,9,6,12,3,8,5,1,2,3,3,2,12,12,9,7,4,8,5,2,12,6,8,10,7,2,10,6,3,7,4,4,5,11,9,2,12,6,4,4,7,9,4,7,
						5,7,1,5,5,9,8,8,1,4,10,7,11,5,6,3,1,12,6,11,3,9,8,12,11,3,1,2,2,10,6,2,9,2,9,2,1,8,3,7,8,3,3,9,	10,	12,	10,	10,3,1,11,6,2,10,
						10,5,3,12,9,4,9,9,1,5,10,12,10,7,12,6,5,6,1,8,3,5,12,2,1,2,6,10,5,9,10,1,10,11,6,2,9,6,3,9,9,12,10,3,12,2,7,11,10,8,12,10,4,12,7,8,11,7,4,4,5,2,7,11,6,6,11,6,8 };

	//Setup every node in the graph
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			graph[i][j] = new Nodes;
			graph[i][j]->num1 = i;
			graph[i][j]->num2 = j;
			graph[i][j]->open = true;
		}
	}
	graph[3][3]->open = false;
	graph[3][4]->open = false;
	graph[6][7]->end = true;
	//Place the weights on the edges and making sure they check the weights of the ones above it so 
	//the weight is forward and backwards
	//Place a blank node and -1 for empty nodes or places outside the graph
	for (int k = 0; k < 10; k++)
	{
		int k1 = k + 1, k2 = k - 1;
		for (int l = 0; l < 10; l++)
		{
			int l1 = l + 1, l2 = l - 1;
			if (k1 != 10 && graph[k + 1][l] != NULL && graph[k][l] != NULL)
			{
				graph[k][l]->adjacent.push_back(std::make_pair(graph[k + 1][l], setup[set_Num]));

				set_Num++;
			}
			else
			{
				graph[k][l]->adjacent.push_back(std::make_pair(Blank, -1));
			}
			if (l1 != 10 && graph[k][l+1] != NULL && graph[k][l] != NULL)
			{
				graph[k][l]->adjacent.push_back(std::make_pair(graph[k][l + 1], setup[set_Num]));

				set_Num++;
			}
			else
			{
				graph[k][l]->adjacent.push_back(std::make_pair(Blank, -1));
			}
			if (k2 != -1 && graph[k - 1][l] != NULL && graph[k][l] != NULL)
			{
				graph[k][l]->adjacent.push_back(std::make_pair(graph[k - 1][l], graph[k - 1][l]->adjacent[0].second));

			}
			else
			{
				graph[k][l]->adjacent.push_back(std::make_pair(Blank, -1));
			}
			if (l2 != -1 && graph[k][l-1] != NULL && graph[k][l] != NULL)
			{
				graph[k][l]->adjacent.push_back(std::make_pair(graph[k][l-1], graph[k][l-1]->adjacent[1].second));

			}
			else
			{
				graph[k][l]->adjacent.push_back(std::make_pair(Blank, -1));
			}
			if (l2 != -1 && k1 != 10 && graph[k+1][l - 1] != NULL && graph[k][l] != NULL)
			{
				graph[k][l]->adjacent.push_back(std::make_pair(graph[k + 1][l - 1], setup[set_Num]));

				set_Num++;
			}
			else
			{
				graph[k][l]->adjacent.push_back(std::make_pair(Blank, -1));
			}
			if (l1 != 10 && k1 != 10 && graph[k+1][l +1] != NULL && graph[k][l] != NULL)
			{
				graph[k][l]->adjacent.push_back(std::make_pair(graph[k + 1][l + 1], setup[set_Num]));

				set_Num++;
			}
			else
			{
				graph[k][l]->adjacent.push_back(std::make_pair(Blank, -1));
			}


			if (l2 != -1 && k2 != -1 && graph[k-1][l - 1] != NULL && graph[k][l] != NULL)
			{
				graph[k][l]->adjacent.push_back(std::make_pair(graph[k - 1][l - 1], graph[k - 1][l - 1]->adjacent[5].second));

			}
			else
			{
				graph[k][l]->adjacent.push_back(std::make_pair(Blank, -1));
			}
			
			if (l1 != 10 && k2 != -1 && graph[k-1][l + 1] != NULL && graph[k][l] != NULL)
			{
				graph[k][l]->adjacent.push_back(std::make_pair(graph[k - 1][l + 1], graph[k - 1][l + 1]->adjacent[4].second));

			}
			else
			{
				graph[k][l]->adjacent.push_back(std::make_pair(Blank, -1));
			}
			
		}
	}
	

}
