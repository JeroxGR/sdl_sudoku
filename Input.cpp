#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Input.hpp"
#include "Soduko_Solution.hpp"

void Input::GenerateRandomGameFromFile(int G[9][9])
{
	std::ifstream f("Game.txt");

	int random = (rand() % 100)*9;
	
	std::string line;

	for (int i = 0; i < random; i++)
	{
		getline(f, line);
	}

	for (int i = 0; i < 9; i++)
	{
		getline(f, line);
		for (int j = 0; j < 9; j++)
		{
			G[i][j] = line[j] - '0';
		}
	}

	f.close();
}