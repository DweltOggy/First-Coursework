#include "Menu_Functions.h"
#include "Maze.h"
#include "Maze_Manager.h"
#include <iostream>
#include <time.h>

void opening_Menu()
{
	bool maze_coninue = true;

	
	while (maze_coninue)
	{
		draw_Menu();

		int menu_choice = 0;
		cin >> menu_choice;
		switch (menu_choice)
		{
		case 1:
			run_single_player();
			menu_choice = 0;
				break;
		case 2:
			run_one_maze();
			menu_choice = 0;
				break;
		case 3:
			run_from_loaded();
			menu_choice = 0;
				break;
		case 4:
			run_maze_analysis();
			menu_choice = 0;
				break;
		case 5:
			maze_coninue = false;
			menu_choice = 0;
				break;

		default:
			cout << "selected a valid option!" << endl;
			menu_choice = 0;
				break;
		}
		menu_choice = 0;
	}
}

inline void draw_Menu()
{
	cout << "**************************************************" << endl;
	cout << "*                                                *" << endl;
	cout << "*       Welcome to the maze generator!           *" << endl;
	cout << "*                                                *" << endl;
	cout << "*   1. Generate or load a maze (coursework 1)    *" << endl;
	cout << "*   2. Generate and run a cooprative solve maze  *" << endl;
	cout << "*   3. Load a multiple player maze               *" << endl;
	cout << "*   4. Run maze anlysis on 100 mazes             *" << endl;
	cout << "*   5. Quit                                      *" << endl;
	cout << "*                                                *" << endl;
	cout << "**************************************************" << endl;
}

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
		while (maze_lenght < 15 || maze_lenght > 35)
		{
			cout << " please enter the lenght of the maze between 15 and 35" << endl;
			cin >> maze_lenght;
		}
		while (maze_height < 15 || maze_height > 35)
		{
			cout << " please enter the height of the maze between 15 and 35" << endl;
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
	
	if(the_game->validate_maze())
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
	double wins = 0;
	double losses = 0;
	double partial_deadlocks = 0;
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
	while (test_number < 2 || test_number > 6)
	{
		cout << " please enter the number of player for the mazes to be run between 2 and 6" << endl;
		cin >> test_number;
	}
	Maze_Manager* test_maze = new Maze_Manager;

	cout << "running..." << endl;
	for  (auto i = 0; i < 100; i++)
	{
		test_maze->initilise(test_height, test_lenght, test_number);
		test_maze->generate_player_paths();
		if (test_maze->run_maze())
			++wins;
		else
		{
			++losses;
			if(test_maze->in_partial_deadlock())
				++partial_deadlocks;
		}

		cout << "#";
	}
	cout << endl;
	cout << "Randomly generated mazes in this coniguration were solved without full or partial deadlock :" << wins << " times!"<< endl;
	
	cout << " Thats a win ratio of :" << wins / 100 << "!" << endl;
	cout << "Partial Deadlocks:" << partial_deadlocks << endl;
	cout << "That means " << (partial_deadlocks/losses)*100 << "% of losses were partially solvable"<< endl;
	delete test_maze;
}