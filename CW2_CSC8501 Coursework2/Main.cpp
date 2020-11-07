#include <iostream>
#include <time.h>
#include "Maze.h"
#include "Maze_Manager.h"

using namespace std;

int main()
{
	srand(time(NULL));
	bool is_done = false;

	Maze_Manager the_game;

	the_game.initilise(20, 50, 5);
	//the_game.read_maze("turnTest1");
	the_game.generate_player_paths();

	while (is_done == false)
	{
		the_game.take_turn();

		is_done = the_game.all_players_done();
		//the_game->print_maze();
		char save_maze = 'n';

		cout << " Save Turn? Y/N" << endl;
		cin >> save_maze;
		string file_name;
		switch (save_maze)
		{
		case 'Y':
			cout << "Please enter a file name (without .txt)" << endl;
			cin >> file_name;
			the_game.save_maze(file_name);
			break;
		case 'y':
			cout << "Please enter a file name (without .txt)" << endl;
			cin >> file_name;
			the_game.save_maze(file_name);
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

	//while (game)
	//{
	/*	Maze* game_maze = new Maze;

		int maze_lenght = 0;
		int maze_height = 0;
		int exit_number = 0;

		bool generate = true;*/

		//char answer1 = 'N';
		//cout << " Load Maze? Y/N" << endl;
		//cin >> answer1;

		//switch (answer1)
		//{
		//case 'N':
		//	generate = true;
		//	break;
		//case 'n':
		//	generate = true;
		//	break;
		//case 'Y':
		//	generate = false;
		//	break;
		//case 'y':
		//	generate = false;
		//	break;
		//default:
		//	generate = true;
		//	break;
		//}


		//if (generate)
		//{
		//	while(maze_lenght < 20 || maze_lenght > 70)
		//	{
		//		cout << " please enter the lenght of the maze between 20 and 70" << endl;
		//		cin >> maze_lenght;
		//	}
		//	while (maze_height < 20 || maze_height > 70)
		//	{
		//		cout << " please enter the height of the maze between 20 and 70" << endl;
		//		cin >> maze_height;
		//	}
		//	while (exit_number < 1 || exit_number > 10)
		//	{
		//		cout << " please enter the exits of the maze between 1 and 10" << endl;
		//		cin >> exit_number;
		//	}
		//	game_maze->generate_maze(maze_height, maze_lenght, exit_number);
		//}
		//else
		//{
		//	string file_name;
		//	cout << " please enter the name of the file you wish to load (without .txt)" << endl;
		//	cin >> file_name;
		//	game_maze->read_maze(file_name);

		//}

		//game_maze->print_maze();
		//char save_maze = 'n';
		//	
		//cout << " Save Maze? Y/N" << endl;
		//cin >> save_maze;
		//string file_name;
		//switch (save_maze)
		//{
		//case 'N':
		//	
		//	break;
		//case 'n':
		//	
		//	break;
		//case 'Y':
		//	
		//	cout << "Please enter a file name (without .txt)" << endl;
		//	cin >> file_name;
		//	game_maze->save_maze(file_name);
		//	break;
		//case 'y':
		//	cout << "Please enter a file name (without .txt)" << endl;
		//	cin >> file_name;
		//	game_maze->save_maze(file_name);
		//	break;
		//default:
		//	
		//	break;
		//}

		//char answer2 = 'N';
		//cout << " Again? Y/N" << endl;
		//cin >> answer2;

		//switch (answer2)
		//{
		//case 'N':
		//	game = false;
		//	break;
		//case 'n':
		//	game = false;
		//	break;
		//case 'Y':
		//	game = true;
		//	break;
		//case 'y':
		//	game = true;
		//	break;
		//default:
		//	game = false;
		//	break;
		//}
		//delete game_maze;
	//}
	
	return 0;
}