#include "Maze_Manager.h"


Maze_Manager::Maze_Manager()
{
	
}
Maze_Manager::~Maze_Manager()
{
	the_players.clear();
}


void Maze_Manager::initilise(int height, int length, int exits, int num_mazes)
{
	Maze *temp;
	temp->generate_maze(height, length, exits);
}

void Maze_Manager::generate_player_paths()
{

}
void Maze_Manager::analyze_paths()
{

}


void Maze_Manager::take_turn()
{

}
void Maze_Manager::save_current_turn()
{

}