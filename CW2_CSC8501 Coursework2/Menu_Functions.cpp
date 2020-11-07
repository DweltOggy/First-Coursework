#include "Menu_Functions.h"
#include "Maze.h"
#include "Maze_Manager.h"
#include <iostream>
#include <time.h>

void run_one_maze()
{
	Maze_Manager* the_game = new Maze_Manager;
	int maze_lenght = 0;
	int maze_height = 0;
	int exit_number = 0;
	
	while (maze_lenght < 20 || maze_lenght > 70)
	{
		cout << " please enter the lengtn of the maze between 20 and 70" << endl;
		cin >> maze_lenght;
	}
	while (maze_height < 20 || maze_height > 70)
	{
		cout << " please enter the height of the maze between 20 and 70" << endl;
		cin >> maze_height;
	}
	while (exit_number < 1 || exit_number > 10)
	{
		cout << " please enter the number of player for the maze between 1 and 10" << endl;
		cin >> exit_number;
	}

	the_game->initilise(maze_height, maze_lenght, exit_number);
	the_game->generate_player_paths();

	run_maze(the_game);

	delete the_game;
}

void run_from_loaded()
{
	Maze_Manager* the_game = new Maze_Manager;
	string file_name;
	cout << " please enter the name of the file you wish to load (without .txt)" << endl;
	cin >> file_name;

	the_game->read_maze(file_name);

	if(the_game->the_maze != nullptr)
		run_maze(the_game);
}

void run_maze(Maze_Manager* the_game)
{
	bool is_done = false;
	while (is_done == false)
	{

		the_game->take_turn();

		is_done = the_game->all_players_done();
		//is_done = the_game->in_deadlock();

		char save_maze = 'n';

		cout << " Save Turn? Y/N" << endl;
		cin >> save_maze;
		string file_name;
		switch (save_maze)
		{
		case 'Y':
			cout << "Please enter a file name (without .txt)" << endl;
			cin >> file_name;
			the_game->save_maze(file_name);
			break;
		case 'y':
			cout << "Please enter a file name (without .txt)" << endl;
			cin >> file_name;
			the_game->save_maze(file_name);
			break;
		default:

			break;
		}

		char quit = 'n';

		cout << " Quit current maze? Y/N" << endl;
		cin >> quit;

		switch (quit)
		{
		case 'Y':
			is_done = true;
			break;
		case 'y':
			is_done = true;
			break;
		default:

			break;
		}
	}
}

void run_maze_analysis()
{

}