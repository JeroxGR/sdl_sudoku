#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "constantes.hpp"
#include "Graphics.hpp"
#include "Soduko_Solution.hpp"

void GFX::drawMainLines(SDL_Renderer*& r)
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	for (int i = 0; i < WINDOW_WIDTH; i = i + WINDOW_WIDTH / 3)
	{
		SDL_Rect rect;

		rect.w = 4;
		rect.h = WINDOW_HEIGHT;
		rect.x = WINDOW_WIDTH / 3 + i;
		rect.y = 0;

		SDL_RenderFillRect(r, &rect);

		rect.w = WINDOW_WIDTH;
		rect.h = 4;
		rect.x = 0;
		rect.y = box_size*3 + i;

		SDL_RenderFillRect(r, &rect);
	}

	int j = 0;

	for (int i = 0; i < WINDOW_WIDTH; i = i + WINDOW_WIDTH / 9)
	{
		if (j != 5 && j != 2 && j != 8)
		{
			SDL_Rect rect;

			rect.w = 2;
			rect.h = WINDOW_HEIGHT;
			rect.x = box_size + i;
			rect.y = 0;

			SDL_RenderFillRect(r, &rect);

			rect.w = WINDOW_WIDTH;
			rect.h = 2;
			rect.x = 0;
			rect.y = box_size + i;

			SDL_RenderFillRect(r, &rect);
		}

		j++;
	}
}

void GFX::drawSodukoElements(SDL_Renderer*& r, int G[9][9],int S[9][9],std::vector<Position> Positions)
{
	GFX::drawMainLines(r);
	
	
	int paddingx = 20,paddingy = 6;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (G[i][j] != 0)
			{
				SDL_Color Black = { 0, 0, 0 }, Green = { 0,200,22 }, Red = {255,0,0},ChosedColor;
				TTF_Font* Sans = TTF_OpenFont("GaelleNumber3.ttf", 100);
				std::string text;
				
				//printing the number in the box
				text = std::to_string(G[i][j]);
				
				if (G[i][j] != S[i][j] && isAMissing(i, j, Positions))
				{
					ChosedColor = Red;
				}
				else if (G[i][j] == S[i][j] && isAMissing(i, j, Positions))
				{
					ChosedColor = Green;
				}
				else
				{
					ChosedColor = Black;
				}

				if(!Sans){return;}
				
				SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), ChosedColor);

				// now you can convert it into a texture
				SDL_Texture* Message = SDL_CreateTextureFromSurface(r, surfaceMessage);

				SDL_Rect Message_rect;
				Message_rect.x = (WINDOW_WIDTH/9) *j + paddingx;
				Message_rect.y = (WINDOW_WIDTH / 9) *i + paddingy;
				Message_rect.w = 50;
				Message_rect.h = 100;

				SDL_RenderCopy(r, Message, NULL, &Message_rect);

				SDL_DestroyTexture(Message);
				TTF_CloseFont(Sans);
			}
		}
	}
}


void GFX::drawBlue(SDL_Renderer *&r)
{
	SDL_SetRenderDrawColor(r, 158, 229, 255, 0);

	Uint32 button;

	SDL_PumpEvents();

	int x, y;
	button = SDL_GetMouseState(&x, &y);

	SDL_Rect hori,vert,box;

	hori.w = (int)(WINDOW_WIDTH/9) + 5;
	hori.h = WINDOW_HEIGHT;
	hori.x = box_size * (x/box_size);
	hori.y = 0;
	

	vert.w = WINDOW_WIDTH;
	vert.h = (int)(WINDOW_HEIGHT/9) + 5;
	vert.x = 0;
	vert.y = box_size * (y / box_size);

	int super_box = box_size * 3;
	box.w = (int)(box_size * 3)+5;
	box.h = (int)(box_size * 3)+5;
	box.x = super_box * (x / super_box);
	box.y = super_box * (y / super_box);

	SDL_RenderFillRect(r, &hori);
	SDL_RenderFillRect(r, &vert);
	SDL_RenderFillRect(r, &box);
}


int GFX::CheckAnswer(int value, int G[9][9], int S[9][9], std::vector<Position> Positions, std::vector<Position> &Solved)
{
	//partie logique
	Uint32 button;

	SDL_PumpEvents();

	int x, y;
	button = SDL_GetMouseState(&x, &y);

	int column = (x / box_size);
	int line = (y / box_size);
	
	if (column < 9 && line < 9)
	{
		if (isAMissing(line, column, Positions) && !isAMissing(line, column, Solved))
		{
			G[line][column] = value;

			if (G[line][column] == S[line][column])
			{
				Position p;
				p.x = line;
				p.y = column;

				Solved.push_back(p);
				return 1;
			}
			return 0;
		}
	}
}

int GFX::GameMenu(SDL_Renderer *&r)
{
	bool down = false;
	int box_velocaty = 1;
	SDL_Rect box;

	box.x = WINDOW_WIDTH / 2 - 150 / 2;
	box.y = (WINDOW_HEIGHT / 2 - 150 / 2);
	box.h = 150;
	box.w = 150;

	SDL_Color Black = { 0,0,0 }, White = { 255,255,255 };
	
	TTF_Font* Sans = TTF_OpenFont("GaelleNumber3.ttf", 300);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "WELCOME TO SODUKO", Black);
	SDL_Surface* surfaceGRCH = TTF_RenderText_Solid(Sans, "BY Med GRICH my 1st game don t judge hh", Black);
	SDL_Surface* PPlay = TTF_RenderText_Solid(Sans, "Press P to start playing", Black);
	SDL_Surface* SS = TTF_RenderText_Solid(Sans, "S", White);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(r, surfaceMessage);
	SDL_Texture* GRCH = SDL_CreateTextureFromSurface(r, surfaceGRCH);
	SDL_Texture* Play = SDL_CreateTextureFromSurface(r, PPlay);
	SDL_Texture* S = SDL_CreateTextureFromSurface(r, SS);

	SDL_Rect Message_rect, GRCH_rect, S_rect, Play_rect;
	Message_rect.x = WINDOW_HEIGHT / 2 - 600 / 2;
	Message_rect.y = 50;
	Message_rect.w = 600;
	Message_rect.h = 100;

	GRCH_rect.x = WINDOW_HEIGHT / 2 - 300;
	GRCH_rect.y = 140;
	GRCH_rect.w = 600;
	GRCH_rect.h = 50;

	S_rect.x = WINDOW_HEIGHT / 2 - 50 + 10;
	S_rect.y = WINDOW_HEIGHT / 2 - 50 + 10;
	S_rect.w = 100;
	S_rect.h = 100;

	Play_rect.x = WINDOW_HEIGHT / 2 - 250;
	Play_rect.y = 600;
	Play_rect.w = 500;
	Play_rect.h = 60;

	TTF_CloseFont(Sans);

	while (1)
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return 0;
			}

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_p)
				{
					return 1;
				}
			}
		}

		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderClear(r);

		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		SDL_RenderFillRect(r, &box);


		if (!Sans) { return -1; }

		if (box.y > 330 || box.y < 300)
		{
			box_velocaty *= -1;
		}

		box.y = box.y - box_velocaty;
		S_rect.y = S_rect.y - box_velocaty;

		SDL_RenderCopy(r, Message, NULL, &Message_rect);
		SDL_RenderCopy(r, GRCH, NULL, &GRCH_rect);
		SDL_RenderCopy(r, S, NULL, &S_rect);
		SDL_RenderCopy(r, Play, NULL, &Play_rect);

		SDL_RenderPresent(r);
	
	}
	return 1;
}

int GFX::YouFinished(SDL_Renderer*& r, int n)
{
	bool down = false;
	int animation_velocaty = 3, animation_limit = 60;
	SDL_Rect box;

	box.x = WINDOW_WIDTH / 2 - 150 / 2;
	box.y = (WINDOW_HEIGHT / 2 - 150 / 2);
	box.h = 150;
	box.w = 150;


	SDL_Color Black = { 0,0,0 }, White = { 255,255,255 };

	//fonts
	TTF_Font* Sans = TTF_OpenFont("GaelleNumber3.ttf", 300);


	std::string GRR = "You took ", ns, sc = " seconds";
	ns = std::to_string(n);

	GRR = GRR + ns + sc;

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "CONGRATS YOU FINISHED THE PUZZLE", Black);
	SDL_Surface* surfaceGRCH = TTF_RenderText_Solid(Sans, GRR.c_str(), Black);
	SDL_Surface* PPlay = TTF_RenderText_Solid(Sans, "Press Q to Quit", Black);
	SDL_Surface* SS = TTF_RenderText_Solid(Sans, "S", White);

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(r, surfaceMessage);
	SDL_Texture* GRCH = SDL_CreateTextureFromSurface(r, surfaceGRCH);
	SDL_Texture* Play = SDL_CreateTextureFromSurface(r, PPlay);
	SDL_Texture* S = SDL_CreateTextureFromSurface(r, SS);

	SDL_Rect Message_rect, GRCH_rect, S_rect, Play_rect;
	Message_rect.x = WINDOW_HEIGHT / 2 - 700 / 2;
	Message_rect.y = 50;
	Message_rect.w = 700;
	Message_rect.h = 100;

	GRCH_rect.x = WINDOW_HEIGHT / 2 - 300;
	GRCH_rect.y = 140;
	GRCH_rect.w = 600;
	GRCH_rect.h = 50;

	S_rect.x = WINDOW_HEIGHT / 2 - 50 + 10;
	S_rect.y = WINDOW_HEIGHT / 2 - 50 + 10;
	S_rect.w = 100;
	S_rect.h = 100;

	Play_rect.x = WINDOW_HEIGHT / 2 - 250;
	Play_rect.y = 600;
	Play_rect.w = 500;
	Play_rect.h = 60;

	TTF_CloseFont(Sans);

	while (1)
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return 0;
			}

			if (e.type == SDL_KEYDOWN)
			{

				if (e.key.keysym.sym == SDLK_q)
				{
					return 1;
				}
			}
		}

		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderClear(r);

		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);

		//black box


		SDL_RenderFillRect(r, &box);


		if (!Sans) { return -1; }
		

		SDL_RenderCopy(r, Message, NULL, &Message_rect);
		SDL_RenderCopy(r, GRCH, NULL, &GRCH_rect);
		SDL_RenderCopy(r, S, NULL, &S_rect);
		SDL_RenderCopy(r, Play, NULL, &Play_rect);

		
		SDL_RenderPresent(r);


	}
	return 0;
}