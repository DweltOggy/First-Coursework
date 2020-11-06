#pragma once
#include "Maze.h"

struct Player
{
	coord position;// = coord{ 0,0 };
	vector<coord> path;
	bool finished = false;
};

class Maze_Manager
{
private:
	Maze* game_maze;
	//vector <Maze*> mazes;

	vector<Player> the_players;

	int m_num_mazes;

public:
	Maze_Manager();
	~Maze_Manager();

	void initilise(int height, int length, int exits);
	
	void generate_player_paths();
	void analyze_paths();

	bool all_players_done();

	void take_turn();

	void save_current_turn(string file_name);



};

