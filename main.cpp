#include <iostream>
#include <string>
#include <thread>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>

#include "Soduko_Solution.hpp"
#include "constantes.hpp"
#include "Graphics.hpp"
#include "Input.hpp"

using namespace std;

int main(int argc,char *argv[])
{
	//only use textures dumbass
	
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);

	Mix_Chunk* sound_1;
	sound_1 = Mix_LoadWAV("menu.wav");

	Mix_Chunk* sound_2;
	sound_2 = Mix_LoadWAV("correct.wav");

	Mix_Chunk* sound_3;
	sound_3 = Mix_LoadWAV("wrong.wav");

	Mix_Chunk* sound_4;
	sound_4 = Mix_LoadWAV("win.wav");

	Mix_PlayChannel(-1, sound_1, 0);

	

	srand(time(0)); //pour generer des nombres aleatoires

	int n;
	int G[9][9], S[9][9];

	Input::GenerateRandomGameFromFile(G);

	vector<Position> Positions = findMissingElements(G), Solved;

	solve(G, S);

	SDL_Window* w = SDL_CreateWindow("SODUKO BY GRICH :D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	
	SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_PRESENTVSYNC);

	bool running = true;

	if (GFX::GameMenu(r))
	{
		
		Mix_FreeChunk(sound_1);
		
		while (running)
		{
			SDL_Event e;

			while (SDL_WaitEvent(&e) && !isValide(G))
			{
				if (e.type == SDL_QUIT)
				{
					return 0;
					break;
				}

				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym >= 49 && e.key.keysym.sym <= 57)
					{
						if (GFX::CheckAnswer(e.key.keysym.sym - SDLK_0, G, S, Positions, Solved))
						{
							Mix_PlayChannel(-1, sound_2, 0);
						}
						else
						{
							Mix_PlayChannel(-1, sound_3, 0);
						}
					}

					if (e.key.keysym.sym == SDLK_s)
					{
						setMissingElements(G, Positions);
						solve(G, G);
						running = false;
					}
				}

				SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
				SDL_RenderClear(r);

				GFX::drawBlue(r);

				GFX::drawSodukoElements(r, G, S, Positions);

				SDL_RenderPresent(r);
			}

			n = SDL_GetTicks() / 1000;
		}
		
		SDL_Delay(3000);

		Mix_PlayChannel(-1, sound_4, 0);
		GFX::YouFinished(r,n);
	}

	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	
	return 0;
}