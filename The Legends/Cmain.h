#pragma once
#include "mainCharacter.h"
#include "Sprite.h"
#include "Environment.h"
#include <math.h>
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

	mainCharacter *bob;

};

