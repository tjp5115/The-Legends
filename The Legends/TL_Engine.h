#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "SDL_Setup.h"
class TL_Engine
{
public:
	TL_Engine(bool * quit, int passed_screenWidth, int passed_screenHeight);
	~TL_Engine();
	int screenWidth;
	int screenHeight;
	float *cameraX;
	float *cameraY;
	int *mouseX;
	int *mouseY;
	SDL_Renderer* getRenderer();
	SDL_Event* getMainEvent();
	void update_begin();
	void update_end();
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event *mainEvent;
};

