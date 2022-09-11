#include "SDL_Handler.hpp"

//constructor
SDL_Handler::SDL_Handler(const char* title, int width, int height):window(nullptr),renderer(nullptr)
{
	if (init())
	{
		std::cout << "There was an erreur on initialisation. erreur : " << SDL_GetError() << std::endl;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!window || !renderer)
	{
		std::cout << "There has been an erreur on creating the window/renderer. erreur : " << SDL_GetError() << std::endl;
	}
}

//destructor
SDL_Handler::~SDL_Handler()
{}

//SDL initialiser
bool SDL_Handler::init()
{
	return SDL_Init(SDL_INIT_EVERYTHING) && IMG_Init(IMG_INIT_PNG);
}

void SDL_Handler::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void SDL_Handler::RenderEntity(Entity &e)
{
	//SDL_Rect source,dest;

	//source
	//source.w = 200;
	//source.h = 200;

	//source.x = 0;
	//source.y = 0;

	//dest
	//source.w = 300;
	//source.h = 300;

	//source.x = 0;
	//source.y = 100;

	SDL_Rect src;
	src.x = e.getCurrentFrame().x;
	src.y = e.getCurrentFrame().y;
	src.w = e.getCurrentFrame().w;
	src.h = e.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = e.getX() ;
	dst.y = e.getY() ;
	dst.w = e.getCurrentFrame().w ;
	dst.h = e.getCurrentFrame().h ;

	SDL_RenderCopy(renderer, e.getTex(), &src, &dst);

	//SDL_RenderCopy(renderer,e.getTex(),&source,&dest);
}

void SDL_Handler::Display() const
{
	SDL_RenderPresent(renderer);
}