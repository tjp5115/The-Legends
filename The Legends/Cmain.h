#pragma once
#include "mainCharacter.h"
#include "Sprite.h"
#include "Environment.h"
#include <math.h>
#include "Debug.h"
class Cmain
{
public:
	Cmain(int passed_screenWidth, int passed_screenHeight);
	~Cmain();

	void GameLoop();

private: 
	Environment *forestArea;

	TL_Engine *engine;

	bool quit;
	Debug *debug;
	mainCharacter *bob;

};

