#pragma once
#include <vector>
#include <string>

using namespace std;

struct coord
{
	int x = 0;
	int y = 0;


	bool operator ==(const coord& other)
	{
		return (x == other.x && y == other.y);
	}

	bool operator !=(const coord& other)
	{
		return (x != other.x && y != other.y);
	}

	coord operator = (const coord& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	coord operator -(const coord& other)
	{
		x = x - other.x;
		y = y - other.y;
		return *this;
	}

};

struct cell 
{
	coord pos;
	vector<cell*> neighbors;
	char value = 'X';
	int indexNumber = 0;

	bool traversable = false;

	bool openset = false;
	bool closedset = false;

	double g_score = 0;
	double f_score = 0;
	double h = 0;

	cell* from = nullptr;

	~cell()
	{
		neighbors.clear();
	}
};

class Maze
{
private:

	vector<cell*> traversable_cells;

	void place_exits();
	vector<coord> reconstruct_path(cell* current);
	cell* lowest_F();
	void draw_path(vector<coord> path);

public:
	vector<vector<cell>> *the_maze;
	
	void initilise(int height, int length, int exits);
	int m_height;
	int m_length;
	int m_entrances;

	vector<coord> entrances_coords;
	coord m_center;

	Maze();
	~Maze();

	void generate_maze(int height, int length, int exits);
	void solve_maze(coord start);
	void print_maze();

	void set_maze_coord(coord position, char value);
	
	vector<coord> calculate_path(coord begin, coord target);
	void delete_maze();
	void link_nodes();

	void save_maze(string file_name);
	void read_maze(string file_name);

};

