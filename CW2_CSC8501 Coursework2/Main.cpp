#include <iostream>
#include <time.h>
#include "Maze.h"
#include "Maze_Manager.h"
#include "Menu_Functions.h"

using namespace std;

int main()
{
	srand(time(NULL));

	bool maze_coninue = true;
	cout << "Welcome to the maze generator!" << endl << endl;
	while (maze_coninue)
	{
		int menu_choice = 0;
		
		cout << "1. Generate and run a maze with multiple players" << endl;
		cout << "2. Load a multiple player maze" << endl;
		cout << "3. Run maze anlysis on 100 mazes" << endl;
		cout << "4. Quit " << endl;
		cin >> menu_choice;
		cout <<  endl << endl;

		switch (menu_choice)
		{
		case 1:
			run_one_maze();
			menu_choice = 0;
			break;
		case 2:
			run_from_loaded();
			menu_choice = 0;
			break;
		case 3:
			run_maze_analysis();
			menu_choice = 0;
			break;
		case 4:
			maze_coninue = false;
			menu_choice = 0;
			break;
		default:
			cout << "selected a valid option!" << endl;
			menu_choice = 0;
			break;
		}
	}

	return 0;
}