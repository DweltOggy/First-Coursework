#pragma once
#include "Maze.h"

struct Player
{
	coord position;
	vector<coord> path;
	bool finished = false;
	bool deadlocked = false;
	int index = 0;
};

class Maze_Manager: public Maze
{
private:
	vector<Player> the_players;

	bool solvable = true;

	int m_num_mazes;

public:
	Maze_Manager();

	~Maze_Manager();

	void initilise(int height, int length, int exits);
	
	void generate_player_paths();

	void analyze_paths();

	bool all_players_done();

	bool in_deadlock();

	bool in_partial_deadlock();

	void take_turn();

	bool check_move(int index);

	void read_maze(string file_name);

	bool validate_maze();

	bool run_maze();

};

