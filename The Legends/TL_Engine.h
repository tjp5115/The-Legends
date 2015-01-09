#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "SDL_Setup.h"
#include "Point.h"
#include <vector>
#include <string>
using namespace std;
class TL_Engine
{
public:
	TL_Engine(bool * quit, int passed_screenWidth, int passed_screenHeight);
	~TL_Engine();
	int screenWidth;
	int screenHeight;
	Point *camera;
	Point *mouse;
	SDL_Renderer* getRenderer();
	SDL_Event* getMainEvent();
	void update_begin();
	void update_end();
	bool mouseClickLeft();
	float cameraX(){ return camera->x; }
	float cameraY(){ return camera->y; }
	float mouseX(){ return mouse->x; }
	float mouseY(){ return mouse->y; }
	float getDistance(Point p1, Point p2);

	bool debug;
	vector<string> debugText;
	void addDebugText(string s);
	void updateDebug();
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event *mainEvent;
};

