#pragma once
#include "Maze.h"

struct Player
{
	coord position;
	vector<coord> path;
};

class Maze_Manager
{
private:
	//Maze* game_maze = nullptr;
	vector <Maze*> mazes;

	vector<Player> the_players;

	int m_num_mazes;

public:
	Maze_Manager();
	~Maze_Manager();

	void initilise(int height, int length, int exits, int num_mazes);
	
	void generate_player_paths();
	void analyze_paths();


	void take_turn();
	void save_current_turn();



};

