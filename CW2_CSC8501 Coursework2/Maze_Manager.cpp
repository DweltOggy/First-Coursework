#include "Maze_Manager.h"


Maze_Manager::Maze_Manager()
{
	game_maze = nullptr;
	m_num_mazes = 0;
}
Maze_Manager::~Maze_Manager()
{
	the_players.clear();
	delete game_maze;
	//mazes.clear();
}


void Maze_Manager::initilise(int height, int length, int exits)
{
	game_maze = new Maze;
	game_maze->generate_maze(height, length, exits);

	for (int i = 0; i < exits; i++)
	{
		Player temp;
		temp.position = game_maze->entrances_coords[i];
		the_players.push_back(temp);
	}

}

void Maze_Manager::generate_player_paths()
{
	for (int i = 0; i < the_players.size(); i++)
	{
		the_players[i].path = game_maze->calculate_path(the_players[i].position, game_maze->m_center);
		the_players[i].position = the_players[i].path.back();
	}
}


void Maze_Manager::analyze_paths()
{

}

bool Maze_Manager::all_players_done()
{
	bool answer = true;

	for (int i = 0; i < the_players.size(); i++)
		if (the_players[i].finished == false)
			answer = false;
		
	return answer;
}

void Maze_Manager::take_turn()
{
	for (int i = 0; i < the_players.size(); i++)
	{
		if (the_players[i].finished == false)
		{

			game_maze->set_maze_coord(the_players[i].position, 'o');

			the_players[i].position = the_players[i].path.back();
			the_players[i].path.pop_back();
			game_maze->set_maze_coord(the_players[i].position, 'P');

			if (the_players[i].position == game_maze->m_center)
				the_players[i].finished = true;
			
		}
	}
	game_maze->print_maze();
}
void Maze_Manager::save_current_turn(string file_name)
{
	game_maze->save_maze(file_name);
}