#pragma once
#include "Point.h"
#include "TL_Engine.h"
#include "Sprite.h"
class Players
{
public:
	Players(TL_Engine *p_engine);
	~Players();
	void update();
	void addPlayer(Sprite *s);
private:
	TL_Engine *engine;
	void updateMousePosition();
	int mouseThreshold;
	Point screenmove;
	vector<Sprite*> players;
};

