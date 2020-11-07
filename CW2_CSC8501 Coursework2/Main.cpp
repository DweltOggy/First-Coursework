#include <iostream>
#include <time.h>
#include "Maze.h"
#include "Maze_Manager.h"

using namespace std;

int main()
{
	srand(time(NULL));
	bool is_done = false;

	//Maze_Manager the_game;
	Maze_Manager* the_game = new Maze_Manager;

	the_game->initilise(20, 50, 5);
	//the_game.read_maze("turnTest1");
	//the_game.generate_player_paths();

	while (is_done == false)
	{
		
		the_game->take_turn();

		is_done = the_game->all_players_done();
		is_done = the_game->in_deadlock();

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

		cout << " Quit? Y/N" << endl;
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

	delete the_game;
	return 0;
}