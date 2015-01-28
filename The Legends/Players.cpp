#include "Players.h"


Players::Players(TL_Engine *p_engine)
{
	engine = p_engine;
	screenmove.x = 5;
	screenmove.y = 5;
	mouseThreshold = 15;
}


Players::~Players()
{
}


void Players::update(){
	updateMousePosition();

}

void Players::updateMousePosition(){
	if (engine->mouse->intX() >= engine->screenWidth - mouseThreshold){
		engine->camera->x -= screenmove.x;
	}
	if (engine->mouse->intX() <= mouseThreshold){
		engine->camera->x += screenmove.x;
	}
	if (engine->mouse->intY() >= engine->screenHeight - mouseThreshold){
		engine->camera->y -= screenmove.y;
	}
	if (engine->mouse->intY() <= mouseThreshold){
		engine->camera->y += screenmove.x;
	}
}

void Players::addPlayer(Sprite *s){
	players.push_back(s);
}

