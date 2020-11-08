#pragma once
#include "Menu_Functions.h"
#include "Maze.h"
#include "Maze_Manager.h"

void opening_Menu();

inline void draw_Menu();

void run_single_player();

void run_one_maze();

void run_from_loaded();

void run_maze(Maze_Manager* the_game);

void run_maze_analysis();
