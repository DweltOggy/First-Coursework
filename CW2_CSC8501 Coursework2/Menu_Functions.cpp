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
	
	while (maze_lenght < 25 || maze_lenght > 50)
	{
		cout << " please enter the lengtn of the maze between 25 and 50" << endl;
		cin >> maze_lenght;
	}
	while (maze_height < 25 || maze_height > 50)
	{
		cout << " please enter the height of the maze between 25 and 50" << endl;
		cin >> maze_height;
	}
	while (exit_number < 2 || exit_number > 8)
	{
		cout << " please enter the number of player for the maze between 2 and 8" << endl;
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
	the_game->generate_player_paths();
	
	if(the_game->the_maze != nullptr)
		run_maze(the_game);
}

void run_maze(Maze_Manager* the_game)
{
	bool is_done = false;
	while (is_done == false)
	{

		the_game->take_turn();
		the_game->print_maze();

		is_done = the_game->all_players_done();

		if (the_game->in_deadlock())
			cout << "Maze is in deadlock! You should quit!" << endl;
		

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
	int wins = 0;
	int test_lenght = 0;
	int test_height = 0;
	int test_number = 0;

	while (test_lenght < 25 || test_lenght > 50)
	{
		cout << " please enter the lengtn of the mazes to be run between 25 and 50" << endl;
		cin >> test_lenght;
	}
	while (test_height < 25 || test_height > 50)
	{
		cout << " please enter the height of the mazes to be run between 25 and 50" << endl;
		cin >> test_height;
	}
	while (test_number < 2 || test_number > 8)
	{
		cout << " please enter the number of player for the mazes to be run between 2 and 8" << endl;
		cin >> test_number;
	}

	for  (auto i = 0; i < 50; i++)
	{
		Maze_Manager* test_maze = new Maze_Manager;

		test_maze->initilise(test_height, test_lenght, test_number);
		test_maze->generate_player_paths();

		if (test_maze->run_maze())
			wins++;

		delete test_maze;
	}

	cout << wins << endl;
}