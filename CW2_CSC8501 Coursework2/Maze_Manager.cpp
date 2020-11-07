#include <fstream>
#include <iostream>

#include "Maze_Manager.h"


Maze_Manager::Maze_Manager()
{
	m_num_mazes = 0;
}
Maze_Manager::~Maze_Manager()
{
	the_players.clear();
}


void Maze_Manager::initilise(int height, int length, int exits)
{
	Maze::initilise(height, length, exits);

	for (int i = 0; i < exits; i++)
	{
		Player temp;
		temp.position = entrances_coords[i];
		temp.index = i;
		the_players.push_back(temp);
	}

}

void Maze_Manager::generate_player_paths()
{
	for (int i = 0; i < the_players.size(); i++)
	{
			the_players[i].path = calculate_path(the_players[i].position,m_center);
			the_players[i].path.pop_back();
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
			if(check_move(the_players[i].index))
			{
				set_maze_coord(the_players[i].position, 'o');

				the_players[i].position = the_players[i].path.back();
				the_players[i].path.pop_back();
				set_maze_coord(the_players[i].position, 'P');
				
				if (the_players[i].position == m_center)
					the_players[i].finished = true;
			}
		}
	}
	print_maze();
}

bool Maze_Manager::check_move(int index)
{
	for (int i = 0; i < the_players.size(); i++)
	{
		if (the_players[i].index != index && the_players[i].finished == false)
		{
			if (the_players[index].path.size() > 0)
				if (the_players[index].path.back() == the_players[i].position)
					return false;
			if(the_players[index].path.size() > 0 && the_players[i].path.size() > 0)
				if (the_players[index].path.back() == the_players[i].path.back())
				{
					the_players[index].deadlocked = true;
					the_players[i].deadlocked = true;
					return false;
				}
					
		}
	}
	return true;
}

void Maze_Manager::read_maze(string file_name)
{
	string line;
	ifstream myfile(file_name + ".txt");

	if (myfile.is_open())
	{
		if (the_maze)
		{
			Maze::delete_maze();
			m_height = 0;
			m_length = 0;
			m_entrances = 0;
		}

		the_maze = new vector<vector<cell>>;

		while (getline(myfile, line))
		{
			m_length = line.length();
			
			vector<cell> temp_row;
			for (auto i = 0; i < line.length(); i++)
			{
				cell temp;
				temp.value = line[i];
				temp.pos.y = m_height;
				temp.pos.x = i;
				temp_row.push_back(temp);
				int number_of_Players = 0;

				if (temp.value == 'E')
				{
					coord temp_exit;
					temp_exit.y = m_height;
					temp_exit.x = i;
					entrances_coords.push_back(temp_exit);
				}
				if (temp.value == 'F')
				{
					coord temp_center;
					temp_center.y = m_height;
					temp_center.x = i;
					m_center = temp_center;
				}
				if (temp.value == 'P')
				{
					Player temp_player;
					temp_player.position.y = m_height;
					temp_player.position.x = i;
					temp_player.index = number_of_Players;
					number_of_Players++;
					the_players.push_back(temp_player);
				}
			}


			(*the_maze).push_back(temp_row);
			m_height++;
		}
		myfile.close();
		link_nodes();
	}
	else
		cout << "couldn't open file: " << file_name << ".txt" << endl;
}
