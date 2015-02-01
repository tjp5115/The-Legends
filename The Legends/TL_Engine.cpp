#include "TL_Engine.h"


TL_Engine::TL_Engine(int passed_screenWidth, int passed_screenHeight)
{
	quit = false;
	debug = true;
	
	mousePos = new Point();
	cameraPos = new Point();
	mapPos = new Point();
	mouseClickPos = new Point();

	SDL_Init(SDL_INIT_VIDEO);
	window = NULL;
	window = SDL_CreateWindow("The Legends", 100, 100, passed_screenWidth, passed_screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN );
	SDL_ShowCursor(1);
	if (window == NULL){
		std::cout << "failed to create window" << std::endl;
	}
	SDL_SetWindowGrab(window, SDL_TRUE);
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
	delete cameraPos;
	delete mapPos;
	delete mouseClickPos;
	delete mousePos;
}

SDL_Renderer* TL_Engine::getRenderer(){
	return renderer;
}

SDL_Event* TL_Engine::getMainEvent(){
	return mainEvent;
}


void TL_Engine::update_begin(){
	int x = mousePos->x;
	int y = mousePos->y;
	SDL_GetMouseState(&x, &y);
	mousePos->set(x, y);

	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);

	if (getMainEvent()->type == SDL_KEYDOWN){
		if (getMainEvent()->key.keysym.sym == SDLK_F5){
			debug = !debug;
		}
		if (mainEvent->key.keysym.sym == SDLK_ESCAPE){
			quit = true;
		}
	}

	if (debug){
		debugText.clear();
	}

}
bool TL_Engine::mouseClickLeft(){
	if (mainEvent->button.type == SDL_MOUSEBUTTONUP && mainEvent->button.button == SDL_BUTTON_LEFT){
		return false;
	}
	if (mainEvent->button.button == SDL_BUTTON_LEFT ){
		return true;
	}
	return false;
}
void TL_Engine::updateDebug(){
	std::string t;
	t = "mouseX:     " + to_string(mousePos->x) + "    mouseY    " + to_string(mousePos->y);
	addDebugText(t);
	t = "cameraX:    " + to_string(cameraPos->x) + "        cameraY    " + to_string(cameraPos->y);
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

void TL_Engine::updateMapPos(Point p){
	mapPos->x += p.x;
	mapPos->y += p.y;
}
void TL_Engine::updateMsePos(Point p){
	mousePos->x += p.x;
	mousePos->y += p.y;

}
void TL_Engine::updateMseClickPos(Point p){
	mouseClickPos->x += p.x;
	mouseClickPos->y += p.y;

}
void TL_Engine::updateCamPos(Point p){
	cameraPos->x += p.x;
	cameraPos->y += p.y;

}