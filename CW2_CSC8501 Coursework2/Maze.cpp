#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "Maze.h"


inline double manhattanDistance(coord a, coord b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Maze::Maze()
{
	m_height = 0;
	m_length = 0;
	m_entrances = 0;
	m_center.x = 0;
	m_center.y = 0;

	the_maze = nullptr;
}

Maze::~Maze()
{
	delete_maze();
}

void Maze::delete_maze()
{
	if (the_maze)
	{
		the_maze->clear();
		delete the_maze;
		the_maze = nullptr;
		traversable_cells.clear();
	}
}

void Maze::initilise(int height, int length, int exits)
{
	if (the_maze)
	{
		delete_maze();
		m_height = 0;
		m_length = 0;
		m_entrances = 0;
		entrances_coords.clear();
	}
	m_height = height;
	m_length = length;
	m_entrances = exits;

	m_center.x = length / 2;
	m_center.y = height / 2;

	the_maze = new vector<vector<cell>>(m_height, vector<cell>(m_length));
	
	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_length; j++)
		{
			(*the_maze)[i][j].pos.y = i;
			(*the_maze)[i][j].pos.x = j;
			(*the_maze)[i][j].value = 'X';
		}

	generate_maze(height, length, exits);
}

void Maze::link_nodes()
{
	int counter = 0;

	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_length; j++)
		{
			if ((*the_maze)[i][j].value == ' ' || (*the_maze)[i][j].value == 'E' || 
				(*the_maze)[i][j].value == 'F' || (*the_maze)[i][j].value == 'P' || 
				(*the_maze)[i][j].value == 'o')
			{
				(*the_maze)[i][j].indexNumber = counter;
				(*the_maze)[i][j].traversable = true;
				counter++;
				traversable_cells.push_back(&(*the_maze)[i][j]);
			}
		}

	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_length; j++)
		{
			if ((*the_maze)[i][j].traversable)
				{
				if (i > 0)
					if ((*the_maze)[i - 1][j].traversable == true)
						(*the_maze)[i][j].neighbors.push_back(&(*the_maze)[i - 1][j]);
				
				if (i < m_height - 1)
					if ((*the_maze)[i + 1][j].traversable == true)
						(*the_maze)[i][j].neighbors.push_back(&(*the_maze)[i + 1][j]);
				

				if (j > 0)
					if ((*the_maze)[i][j - 1].traversable == true)
						(*the_maze)[i][j].neighbors.push_back(&(*the_maze)[i][j - 1]);
				
				if (j < m_length - 1)
					if ((*the_maze)[i][j + 1].traversable == true)
						(*the_maze)[i][j].neighbors.push_back(&(*the_maze)[i][j + 1]);	
			}	
		}
}

inline vector<coord> Maze::calculate_path(coord begin, coord target)
{
	vector<coord> thePath;

	cell* start = &(*the_maze)[begin.y][begin.x];
	cell* end = &(*the_maze)[target.y][target.x];

	auto it = traversable_cells.begin();
	while (it != traversable_cells.end())
	{
		(*it)->openset = false;
		(*it)->closedset = false;
		(*it)->from = nullptr;
		(*it)->g_score = 0;
		(*it)->f_score = 0;
		(*it)->h = 0;

		it++;
	}

	vector<cell*> open;
	vector<cell*> closed;

	start->openset = true;
	start->from = nullptr;
	start->g_score = 0;
	start->h = manhattanDistance(start->pos, end->pos);

	start->f_score = start->g_score + manhattanDistance(start->pos, end->pos);

	open.push_back(start);

	while (open.size() > 0)
	{
		cell* current = lowest_F();

		if (current->pos == end->pos)
			return reconstruct_path(current);
		

		current->openset = false;
		current->closedset = true;

		for (int i = 0; i < open.size(); i++)
			if (open[i] == current)
				open.erase(open.begin() + i);
			
			
		

		closed.push_back(current);

		vector<cell*> neighbors = current->neighbors;

		for (int i = 0; i < neighbors.size(); i++)
		{
			float g_score = current->g_score + 1;

			float h_score = manhattanDistance(neighbors[i]->pos, end->pos);

			float f_score = g_score + h_score;

			if(neighbors[i]->closedset == false)
			{
				if ( g_score < neighbors[i]->g_score || neighbors[i]->openset == false)
				{
					neighbors[i]->from = current;
					neighbors[i]->g_score = g_score;
					neighbors[i]->f_score = f_score;
					neighbors[i]->h = h_score;
					if (neighbors[i]->openset == false)
					{
						neighbors[i]->openset = true;
						open.push_back(neighbors[i]);
					}
				}
			}		
		}
	}
	return thePath;
}

inline vector<coord> Maze::reconstruct_path(cell* current)
{
	std::vector<coord> returnPath;
	returnPath.push_back(current->pos);
	cell* loopPtr = current;
	while (loopPtr->from != nullptr)
	{
		loopPtr = loopPtr->from;
		returnPath.push_back(loopPtr->pos);
	}
	return returnPath;
}

inline cell* Maze::lowest_F()
{
	cell* lowestF = traversable_cells[0];
	float currentLowest = 10000000;

	auto it = traversable_cells.begin();
	while (it != traversable_cells.end())
	{
		if ((*it)->f_score < currentLowest && (*it)->openset == true)
		{
			currentLowest = (*it)->f_score;
			lowestF = traversable_cells[(*it)->indexNumber];
		}
		it++;
	}
	return lowestF;
}

void Maze::draw_path(vector<coord> path)
{
	for (auto i = 0; i < path.size(); i++)
		(*the_maze)[path[i].y][path[i].x].value = 'o';
}

void Maze::solve_maze()
{
	for(auto i = 0; i < entrances_coords.size();i++)
		draw_path(calculate_path(m_center, entrances_coords[i]));
}

void Maze::generate_maze(int height, int length, int exits)
{
	place_exits();

	for (int i = 1; i < m_height - 1; i++)
		for (int j = 1; j < m_length - 1; j++)
		{
			int random = rand() % 10;
			if (random < 7)
				(*the_maze)[i][j].value = ' ';
		}

	for (int i = 1; i < m_height - 1 ; i++)
		for (int j = 1; j < m_length-1; j++)
		{
			if (j == 1 || j == (m_length - 2))
				(*the_maze)[i][j].value = ' ';

			if (i == 1 || i == (m_height - 2))
				(*the_maze)[i][j].value = ' ';
		}
	
	for (int i = m_center.y; i < m_height - 1; i++)
	{
		(*the_maze)[i][m_center.x].value = ' ';
		for (int j = m_center.x; j < m_length - 1; j++)
			(*the_maze)[m_center.y][j].value = ' ';
	}

	for (int i = m_center.y; i > 0; i--)
		(*the_maze)[i][m_center.x].value = ' ';

	for (int i = m_center.y - 3 ; i < m_center.y + 3; i++)
		for (int j = m_center.x - 3; j < m_center.x + 3; j++)
			(*the_maze)[i][j].value = ' ';

	link_nodes();

	(*the_maze)[m_center.y][m_center.x].value = 'F';

	for (int i = 0; i < m_entrances; i++)
		(*the_maze)[entrances_coords[i].y][entrances_coords[i].x].value = 'E';
	
}

void Maze::place_exits()
{	
	for (int i = 0; i < m_entrances; i++)
	{
		bool check1 = rand() % 2;
		bool check2 = rand() % 2;

		coord exit;

		if (check1 && check2)
		{
			exit.y = 0;
			exit.x = rand() % m_length;
			while(exit.x == 0 || exit.x == (m_length - 1) || (*the_maze)[exit.y][exit.x].value == 'E')
				exit.x = rand() % m_length;

		}
		else if(check1 && !check2)
		{
			exit.y = m_height - 1;
			exit.x = rand() % m_length;
			while (exit.x == 0 || exit.x == (m_length - 1) || (*the_maze)[exit.y][exit.x].value == 'E')
				exit.x = rand() % m_length;

		}
		else if (!check1 && check2)
		{
			exit.x = 0;
			exit.y = rand() % m_height;
			while (exit.y == 0 || exit.y == (m_height - 1) ||(*the_maze)[exit.y][exit.x].value == 'E')
				exit.y = rand() % m_height;

		}
		else if (!check1 && !check2)
		{
			exit.x = m_length - 1;
			exit.y = rand() % m_height;
			while (exit.y == 0 || exit.y == (m_height - 1) || (*the_maze)[exit.y][exit.x].value == 'E')
				exit.y = rand() % m_height;

		}

		entrances_coords.push_back(exit);
		(*the_maze)[exit.y][exit.x].value = 'E';
	}
}

void Maze::print_maze()
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_length; j++)
			cout << (*the_maze)[i][j].value;
				
		cout << endl;
	}
}

void Maze::save_maze(string file_name)
{
	ofstream myfile;
	myfile.open(file_name + ".txt");

	if (the_maze)
	{
		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_length; j++)
			{
				myfile <<(*the_maze)[i][j].value;
			}
			myfile << "\n";
		}
	}
	myfile.close();
}

void Maze::read_maze(string file_name)
{
	string line;
	ifstream myfile(file_name + ".txt");

	if (myfile.is_open())
	{
		if (the_maze)
		{
			delete_maze();
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
					//entrances_coords.push_back(temp_exit);
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

void Maze::set_maze_coord(coord position, char value)
{
	(*the_maze)[position.y][position.x].value = value;
}