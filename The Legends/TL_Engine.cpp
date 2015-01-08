#include "TL_Engine.h"


TL_Engine::TL_Engine(bool * quit, int passed_screenWidth, int passed_screenHeight)
{
	mouseX = (int*)malloc(sizeof(int*));
	*mouseX = 0;

	mouseY = (int*)malloc(sizeof(int*));
	*mouseY = 0;

	cameraX = (float*)malloc(sizeof(float*));
	*cameraX = 0;

	cameraY = (float*)malloc(sizeof(float*));
	*cameraY = 0;

	SDL_Init(SDL_INIT_VIDEO);
	window = NULL;
	window = SDL_CreateWindow("The Legends", 100, 100, passed_screenWidth, passed_screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (window == NULL){
		std::cout << "failed to create window" << std::endl;
		*quit = true;
	}

	screenHeight = passed_screenHeight;
	screenWidth = passed_screenWidth;

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainEvent = new SDL_Event();
}


TL_Engine::~TL_Engine()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer* TL_Engine::getRenderer(){
	return renderer;
}

SDL_Event* TL_Engine::getMainEvent(){
	return mainEvent;
}


void TL_Engine::update_begin(){
	SDL_GetMouseState(mouseX, mouseY);
	SDL_PollEvent(getMainEvent());
	SDL_RenderClear(getRenderer());
}

void TL_Engine::update_end(){
	SDL_RenderPresent(getRenderer());
}