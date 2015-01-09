#include "TL_Engine.h"


TL_Engine::TL_Engine(bool * quit, int passed_screenWidth, int passed_screenHeight)
{
	debug = true;

	mouse = new Point(0, 0);
	camera = new Point(0, 0);
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
	debugText.clear();
	delete camera;
	delete mouse;
}

SDL_Renderer* TL_Engine::getRenderer(){
	return renderer;
}

SDL_Event* TL_Engine::getMainEvent(){
	return mainEvent;
}


void TL_Engine::update_begin(){
	int x = mouse->x;
	int y = mouse->y;
	SDL_GetMouseState(&x, &y);
	mouse->set(x, y);

	SDL_PollEvent(getMainEvent());
	SDL_RenderClear(getRenderer());

	if (getMainEvent()->type == SDL_KEYDOWN){
		if (getMainEvent()->key.keysym.sym == SDLK_F5){
			debug = !debug;
		}
	}

	if (debug){
		debugText.clear();
	}

}
bool TL_Engine::mouseClickLeft(){
	if (getMainEvent()->type == SDL_MOUSEBUTTONDOWN || getMainEvent()->type == SDL_MOUSEMOTION){
		if (getMainEvent()->button.button == SDL_BUTTON_LEFT){
			return true;
		}
	}
	return false;
}
void TL_Engine::updateDebug(){
	std::string t;
	t = "mouseX:     " + to_string(mouse->x) + "    mouseY    " + to_string(mouse->y);
	addDebugText(t);
	t = "cameraX:    " + to_string(camera->x) + "        cameraY    " + to_string(camera->y);
	addDebugText(t);
}
void TL_Engine::update_end(){
	SDL_RenderPresent(getRenderer());
}
float TL_Engine::getDistance(Point p1, Point p2){
	float diffx = p1.x - p2.x;
	float diffy = p1.y - p2.y;

	return (float)sqrt((diffx * diffx) + (diffy * diffy));
}

void TL_Engine::addDebugText(string s){
	debugText.push_back(s);
}