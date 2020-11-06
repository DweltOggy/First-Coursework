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

class Maze
{
private:

	struct cell 
	{
		coord pos;
		vector<cell*> neighbors;
		char value = 'X';
		int indexNumber = 0;

		//bool visited = false;
		bool traversable = false;

		bool openset = false;
		bool closedset = false;

		double g_score = 0;
		double f_score = 0;
		double h = 0;

		//cell* CurrentPtr;
		//cell* NextPtr;
		cell* from = nullptr;

	};

	int m_height;
	int m_length;
	int m_entrances;

	

	vector<vector<cell>> *the_maze;
	vector<cell*> traversable_cells;

	
	
	void initilise(int height, int length, int exits);
	void link_nodes();
	void delete_maze();
	void place_exits();

	
	vector<coord> reconstruct_path(cell* current);
	cell* lowest_F();
	


	void draw_path(vector<coord> path);

	
public:

	vector<coord> entrances_coords;
	coord m_center;

	Maze();
	~Maze();

	void generate_maze(int height, int length, int exits);
	void solve_maze(coord start);
	void print_maze();

	void set_maze_coord(coord position, char value);
	
	vector<coord> calculate_path(coord begin, coord target);

	void save_maze(string file_name);
	void read_maze(string file_name);

};

