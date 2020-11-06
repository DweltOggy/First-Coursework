#include <iostream>
#include <time.h>
#include "Maze.h"
#include "Maze_Manager.h"

using namespace std;

int main()
{
	srand(time(NULL));
	bool game = false;

	Maze_Manager the_game;


	while (game)
	{
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
	}
	
	return 0;
}