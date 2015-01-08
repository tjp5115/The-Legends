#pragma once
#include "Sprite.h"

class Tree
{
public:
	Tree(TL_Engine *p_engine, int x, int y, float *cameraX, float *cameraY);
	~Tree();

	void drawCrown();
	void drawTrunk();

	int getX(){ return x; };
	int getY(){ return y; };

	Sprite* getTrunk(){ return trunk; }
	Sprite* getCrown(){ return crown; }

	float *cameraX;
	float *cameraY;
private:
	int x, y;
	TL_Engine *engine;
	Sprite *crown;
	Sprite *trunk;
};

