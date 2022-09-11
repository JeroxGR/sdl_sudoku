#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

#include "constantes.hpp"
#include "Soduko_Solution.hpp"


namespace GFX
{
	void drawMainLines(SDL_Renderer *&r);

	void drawSodukoElements(SDL_Renderer*& r, int G[9][9],int S[9][9], std::vector<Position> Positions);

	void drawBlue(SDL_Renderer*& r);

	int CheckAnswer(int value, int G[9][9], int S[9][9], std::vector<Position> Positions, std::vector<Position> &Solved);

	int GameMenu(SDL_Renderer*& r);

	int YouFinished(SDL_Renderer*& r, int n);
}
