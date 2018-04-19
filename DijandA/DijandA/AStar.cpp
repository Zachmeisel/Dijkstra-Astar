#include "AStar.h"



AStar::AStar()
{
}


AStar::~AStar()
{
}
using namespace std;

#define ROW 10
#define COL 10

typedef pair<int, int> Pair;

typedef pair<double, pair<int, int>> pPair;

struct cell
{
	// Row and Column index of its parent
	int parent_i, parent_j;

	double f, g, h;
};

bool isValid(int row, int col)
{

	return (row >= 0) && (row < ROW) &&
		(col >= 0) && (col < COL);
}


bool isUnBlocked(Nodes* grid[][10], int row, int col)
{

	if (grid[row][col]->open == true)
		return (true);
	else
		return (false);
}


bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

double calculateHValue(int row, int col, Pair dest)
{
	// Return using the distance formula
	return ((double)sqrt((row - dest.first)*(row - dest.first)
		+ (col - dest.second)*(col - dest.second)+(row + col - dest.first + dest.second)*(row + col - dest.first + dest.second)));

}

void tracePath(cell cellDetails[][COL], Pair dest, Nodes * grid[][10])
{
	std::cout << "\nThe Path is ";
	int row = dest.first;
	int col = dest.second;
	int weight = 0;
	int temp1=0, temp2=0;
	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
		&& cellDetails[row][col].parent_j == col))
	{
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty())
	{
		pair<int, int> p = Path.top();

		Path.pop();
		temp1 = temp1 - p.first;
		temp2 = temp2 - p.second;

		//Add up the weight
		if (temp1 == 1 && temp2 == 0)
		{
			weight += grid[p.first][p.second]->adjacent[0].second;
		}
		if (temp1 == -1 && temp2 == 0)
		{
			weight += grid[p.first][p.second]->adjacent[2].second;
		}
		if (temp1 == 0 && temp2 == 1)
		{
			weight += grid[p.first][p.second]->adjacent[1].second;
		}
		if (temp1 == 0 && temp2 == -1)
		{
			weight += grid[p.first][p.second]->adjacent[3].second;
		}

		if (temp1 == 1 && temp2 == 1)
		{
			weight += grid[p.first][p.second]->adjacent[5].second;
		}
		if (temp1 == 1 && temp2 == -1)
		{
			weight += grid[p.first][p.second]->adjacent[4].second;
		}
		if (temp1 == -1 && temp2 == 1)
		{
			weight += grid[p.first][p.second]->adjacent[7].second;
		}
		if (temp1 == -1 && temp2 == -1)
		{
			weight += grid[p.first][p.second]->adjacent[6].second;
		}

		printf("-> (%d,%d) ", p.first, p.second);
		temp1 = p.first;
		temp2 = p.second;
	}
	std::cout << "\nThe final weight is: " << weight << endl;
	return;
}
void AStar::aStarSearch(Nodes* grid[][10], Pair src, Pair dest)
{

	if (isValid(src.first, src.second) == false)
	{
		std::cout << "Source is invalid\n";
		return;
	}


	if (isValid(dest.first, dest.second) == false)
	{
		std::cout << "Destination is invalid\n";
		return;
	}

	if (isUnBlocked(grid, src.first, src.second) == false ||
		isUnBlocked(grid, dest.first, dest.second) == false)
	{
		std::cout << "Source or the destination is blocked\n";
		return;
	}


	if (isDestination(src.first, src.second, dest) == true)
	{
		std::cout << "We are already at the destination\n";
		return;
	}

	// Create a closed list and initialise it to false 

	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	cell cellDetails[ROW][COL];

	int i, j;

	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;


	set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the open list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		double gNew, hNew, fNew;

		//1st (North)

		if (isValid(i - 1, j) == true)
		{

			if (grid[i - 1][j]->end == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				std::cout << "The destination cell is found\n";
				tracePath(cellDetails, dest, grid);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j] == false &&
				isUnBlocked(grid, i - 1, j) == true)
			{
				gNew = grid[i][j]->adjacent[2].second;
				hNew = calculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. 
				// If it is on the open list already, check
				// to see if this path using f cost as the measure.
				if (cellDetails[i - 1][j].f == FLT_MAX ||
					cellDetails[i - 1][j].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i - 1, j)));

					// Update the details of this cell
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		//2nd (South)

		if (isValid(i + 1, j) == true)
		{

			if (grid[i + 1][j]->end == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				std::cout << "The destination cell is found\n";
				tracePath(cellDetails, dest,grid);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i + 1][j] == false &&
				isUnBlocked(grid, i + 1, j) == true)
			{
				gNew = grid[i][j]->adjacent[0].second;
				hNew = calculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. 
				// If it is on the open list already, check
				// to see if this path using f cost as the measure.
				if (cellDetails[i + 1][j].f == FLT_MAX ||
					cellDetails[i + 1][j].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i + 1, j)));
					// Update the details of this cell
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		//3rd (East)

		if (isValid(i, j + 1) == true)
		{

			if (grid[i][j + 1]->end == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				std::cout << "The destination cell is found\n";
				tracePath(cellDetails, dest,grid);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j + 1] == false &&
				isUnBlocked(grid, i, j + 1) == true)
			{
				gNew = grid[i][j]->adjacent[1].second;
				hNew = calculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. 
				// If it is on the open list already, check
				// to see if this path using f cost as the measure.
				if (cellDetails[i][j + 1].f == FLT_MAX ||
					cellDetails[i][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i, j + 1)));

					// Update the details of this cell
					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		//4th (West)

		if (isValid(i, j - 1) == true)
		{

			if (grid[i][j - 1]->end == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				std::cout << "The destination cell is found\n";
				tracePath(cellDetails, dest,grid);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j - 1] == false &&
				isUnBlocked(grid, i, j - 1) == true)
			{
				gNew = grid[i][j]->adjacent[3].second;
				hNew = calculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. 
				// If it is on the open list already, check
				// to see if this path using f cost as the measure.
				if (cellDetails[i][j - 1].f == FLT_MAX ||
					cellDetails[i][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i, j - 1)));

					// Update the details of this cell
					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}

		//5th (North-East)

		if (isValid(i - 1, j + 1) == true)
		{

			if (grid[i - 1][j + 1]->end == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
				std::cout << "The destination cell is found\n";
				tracePath(cellDetails, dest,grid);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j + 1] == false &&
				isUnBlocked(grid, i - 1, j + 1) == true)
			{
				gNew = grid[i][j]->adjacent[7].second;
				hNew = calculateHValue(i - 1, j + 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. 
				// If it is on the open list already, check
				// to see if this path using f cost as the measure.
				if (cellDetails[i - 1][j + 1].f == FLT_MAX ||
					cellDetails[i - 1][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i - 1, j + 1)));

					// Update the details of this cell
					cellDetails[i - 1][j + 1].f = fNew;
					cellDetails[i - 1][j + 1].g = gNew;
					cellDetails[i - 1][j + 1].h = hNew;
					cellDetails[i - 1][j + 1].parent_i = i;
					cellDetails[i - 1][j + 1].parent_j = j;
				}
			}
		}

		//6th (North-West)

		if (isValid(i - 1, j - 1) == true)
		{

			if (grid[i - 1][j - 1]->end == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
				std::cout << "The destination cell is found\n";
				tracePath(cellDetails, dest,grid);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j - 1] == false &&
				isUnBlocked(grid, i - 1, j - 1) == true)
			{
				gNew = grid[i][j]->adjacent[6].second;
				hNew = calculateHValue(i - 1, j - 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. 
				// If it is on the open list already, check
				// to see if this path using f cost as the measure.
				if (cellDetails[i - 1][j - 1].f == FLT_MAX ||
					cellDetails[i - 1][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));
					// Update the details of this cell
					cellDetails[i - 1][j - 1].f = fNew;
					cellDetails[i - 1][j - 1].g = gNew;
					cellDetails[i - 1][j - 1].h = hNew;
					cellDetails[i - 1][j - 1].parent_i = i;
					cellDetails[i - 1][j - 1].parent_j = j;
				}
			}
		}

		//7th (South-East)

		if (isValid(i + 1, j + 1) == true)
		{

			if (grid[i + 1][j + 1]->end == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
				std::cout << "The destination cell is found\n";
				tracePath(cellDetails, dest,grid);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i + 1][j + 1] == false &&
				isUnBlocked(grid, i + 1, j + 1) == true)
			{
				gNew = grid[i][j]->adjacent[5].second;
				hNew = calculateHValue(i + 1, j + 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. 
				// If it is on the open list already, check
				// to see if this path using f cost as the measure.
				if (cellDetails[i + 1][j + 1].f == FLT_MAX ||
					cellDetails[i + 1][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i + 1, j + 1)));

					// Update the details of this cell
					cellDetails[i + 1][j + 1].f = fNew;
					cellDetails[i + 1][j + 1].g = gNew;
					cellDetails[i + 1][j + 1].h = hNew;
					cellDetails[i + 1][j + 1].parent_i = i;
					cellDetails[i + 1][j + 1].parent_j = j;
				}
			}
		}

		//8th (South-West)

		if (isValid(i + 1, j - 1) == true)
		{

			if (grid[i + 1][j - 1]->end == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
				std::cout << "The destination cell is found\n";
				tracePath(cellDetails, dest,grid);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i + 1][j - 1] == false &&
				isUnBlocked(grid, i + 1, j - 1) == true)
			{
				gNew = grid[i][j]->adjacent[4].second;
				hNew = calculateHValue(i + 1, j - 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. 
				// If it is on the open list already, check
				// to see if this path using f cost as the measure.
				if (cellDetails[i + 1][j - 1].f == FLT_MAX ||
					cellDetails[i + 1][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i + 1, j - 1)));

					// Update the details of this cell
					cellDetails[i + 1][j - 1].f = fNew;
					cellDetails[i + 1][j - 1].g = gNew;
					cellDetails[i + 1][j - 1].h = hNew;
					cellDetails[i + 1][j - 1].parent_i = i;
					cellDetails[i + 1][j - 1].parent_j = j;
				}
			}
		}
	}

	// If no destination is found or if the cell is not marked correctly
	if (foundDest == false)
		std::cout << "Failed to find the Destination Cell\n";

	return;
}
