#pragma once
#include "mainCharacter.h"
#include "Sprite.h"
#include "Environment.h"
#include <math.h>
#include "Debug.h"
#include "Players.h"
class Cmain
{
public:
	Cmain(int passed_screenWidth, int passed_screenHeight);
	~Cmain();

	void GameLoop();

private: 
	Environment *forestArea;
	Players *players;
	mainCharacter *bob;

	TL_Engine *engine;

	Debug *debug;

};

