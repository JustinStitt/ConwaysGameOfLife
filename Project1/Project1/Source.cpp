#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <iomanip>

using namespace std;

const int num_cells = 1000;
const int cells_per_row = 50;
const int cells_per_col = num_cells / cells_per_row;//20
int gen = 1;


int num_neighbors(vector<vector<int>>& cells, int x)
{
	int total = 0;
	//check how many alive neighbors a given cell has
	if (x >= cells_per_row)//above
	{
		if (cells[x - cells_per_row][0] == 1)
			total++;
	}
	if (x < (num_cells - cells_per_row))//below
	{
		if (cells[x + cells_per_row][0] == 1)
			total++;
	}
	if (x % cells_per_row != (cells_per_row - 1))//RIGHT
	{
		if (cells[x + 1][0] == 1)
			total++;
	}
	if (x % cells_per_row != 0)//LEFT
	{
		if (cells[x - 1][0] == 1)
			total++;
	}
	if ((x % cells_per_row != (cells_per_row - 1)) && (x >= cells_per_row))//TOP_RIGHT
	{
		if (cells[x - (cells_per_row - 1)][0] == 1)
			total++;
	}
	if ((x % cells_per_row != 0) && (x > cells_per_row))//TOP_LEFT
	{
		if (cells[x - (cells_per_row + 1)][0] == 1)
			total++;
	}
	if ((x % cells_per_row != (cells_per_row - 1)) && (x < num_cells - cells_per_row))//BOT_RIGHT
	{
		if (cells[x + (cells_per_row + 1)][0] == 1)
			total++;
	}
	if (x % cells_per_row != 0 && x < num_cells - cells_per_row)//BOT_LEFT
	{
		if (cells[x + (cells_per_row - 1)][0] == 1)
			total++;
	}
	return total;
}

void update_cells(vector<vector<int>>& cells)
{
	vector<vector<int>> cells_copy = cells;
	for (int x = 0; x < cells.size(); x++)
	{
		int _neighbors = num_neighbors(cells, x);
		if ((_neighbors == 2 || _neighbors == 3) && cells_copy[x][0] == 1)
		{//any alive cell with 2 or 3 neighbors survives
		 //cell survives
		}
		else if (cells_copy[x][0] == 0 && _neighbors == 3)
		{
			//becomes alive
			cells_copy[x][0] = 1;//set alive bit to 1 (is alive)
		}
		else
		{//the cell dies
			cells_copy[x][0] = 0;//set alive it to 0 (is not alive)
		}
	}
	cells = cells_copy;
	gen++;
}

void draw_cells(vector<vector<int>>& cells)
{
	system("CLS");
	int count = 0;
	for (vector<int> cell : cells)
	{
		if (count == cells_per_row)
		{
			cout << endl;
			count = 0;
		}
		if (cell[0] == 1)//cell is alive
			cout << '*';
		else
			cout << " ";
		cout << " ";
		count++;
	}
	cout << endl;
	cout << "Generation: #" << gen;
}

int main()
{
	srand(time(0));//seed our random gen with curr time
	bool running = true;

	vector<vector<int>> cells;//{alive,# of neighbors}
	for (int x = 0; x < num_cells; x++)
	{//all cells start dead
		cells.push_back({ 0 });//rand() % 2
	}

	//vector<int> init_list = { 52,53,54 }; //{52,55,106,156,206,205,204,203,152} glider LWSS (light-weight space ship)
	//for (int val : init_list)
	//cells[val][0] = 1;
	for (vector<int>& cell : cells)
	{
		if (rand() % 5 == 2)
			cell[0] = 1;
	}

	cout << num_neighbors(cells, 52);


	while (running)
	{
		draw_cells(cells);

		update_cells(cells);
	}


	cin.get();
	return 0;
}