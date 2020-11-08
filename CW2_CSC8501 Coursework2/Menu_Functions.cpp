#include "Menu_Functions.h"
#include "Maze.h"
#include "Maze_Manager.h"
#include <iostream>
#include <time.h>

void run_single_player()
{
	Maze* game_maze = new Maze;

	int maze_lenght = 0;
	int maze_height = 0;
	int exit_number = 0;

	bool generate = true;

	char answer1 = 'N';
	cout << " Load Maze? Y/N" << endl;
	cin >> answer1;

	switch (answer1)
	{
	case 'N':
		generate = true;
			break;
	case 'n':
		generate = true;
			break;
	case 'Y':
		generate = false;
			break;
	case 'y':
		generate = false;
		break;
	default:
		generate = true;
		break;
	}


	if (generate)
	{
		while (maze_lenght < 20 || maze_lenght > 70)
		{
			cout << " please enter the lenght of the maze between 20 and 70" << endl;
			cin >> maze_lenght;
		}
		while (maze_height < 20 || maze_height > 70)
		{
			cout << " please enter the height of the maze between 20 and 70" << endl;
			cin >> maze_height;
		}
		while (exit_number < 1 || exit_number > 10)
		{
			cout << " please enter the exits of the maze between 1 and 10" << endl;
			cin >> exit_number;
		}
		game_maze->initilise(maze_height, maze_lenght, exit_number);
		game_maze->solve_maze();
	}
	else
	{
		string file_name;
		cout << " please enter the name of the file you wish to load (without .txt)" << endl;
		cin >> file_name;
		game_maze->read_maze(file_name);

	}
		
	game_maze->print_maze();
	char save_maze = 'n';

	cout << " Save Maze? Y/N" << endl;
	cin >> save_maze;
	string file_name;
	switch (save_maze)
	{
	case 'Y':
		cout << "Please enter a file name (without .txt)" << endl;
		cin >> file_name;
		game_maze->save_maze(file_name);
		break;
	case 'y':
		cout << "Please enter a file name (without .txt)" << endl;
		cin >> file_name;
		game_maze->save_maze(file_name);
		break;
	default:

		break;
	}

	delete game_maze;
	
}

void run_one_maze()
{
	Maze_Manager* the_game = new Maze_Manager;
	int maze_lenght = 0;
	int maze_height = 0;
	int exit_number = 0;
	
	while (maze_lenght < 15 || maze_lenght > 35)
	{
		cout << " please enter the lengtn of the maze between 15 and 35" << endl;
		cin >> maze_lenght;
	}
	while (maze_height < 15 || maze_height > 35)
	{
		cout << " please enter the height of the maze between 15 and 35" << endl;
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

	delete the_game;
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

	while (test_lenght < 15 || test_lenght > 35)
	{
		cout << " please enter the lengtn of the mazes to be run between 15 and 35" << endl;
		cin >> test_lenght;
	}
	while (test_height < 15 || test_height > 35)
	{
		cout << " please enter the height of the mazes to be run between 15 and 35" << endl;
		cin >> test_height;
	}
	while (test_number < 2 || test_number > 8)
	{
		cout << " please enter the number of player for the mazes to be run between 2 and 8" << endl;
		cin >> test_number;
	}
	Maze_Manager* test_maze = new Maze_Manager;

	cout << "running..." << endl;
	for  (auto i = 0; i < 100; i++)
	{
		test_maze->initilise(test_height, test_lenght, test_number);
		test_maze->generate_player_paths();
		if (test_maze->run_maze())
			wins++;
		cout << "#";
	}
	cout << endl;
	cout << "Randomly generated mazes in this coniguration were solved without full deadlock :" << wins << " times!"<< endl;
	cout << " Thats a win ratio of :" << (double)wins / 100 << "!" << endl;

	delete test_maze;
	cout << wins << endl;
}