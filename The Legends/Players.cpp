#include "Players.h"


Players::Players(TL_Engine *p_engine)
{
	engine = p_engine;
	screenmove.x = 5;
	screenmove.y = 5;
	mouseThreshold = 5;
}


Players::~Players()
{
}


void Players::update(){
	updateMousePosition();

}

void Players::updateMousePosition(){
	if (engine->getMsePos().intX() >= engine->screenWidth - mouseThreshold){
		//engine->camera->x -= screenmove.x;
		engine->updateCamPos(Point(-screenmove.x,0));
	}
	if (engine->getMsePos().intX() <= mouseThreshold){
		//engine->camera->x += screenmove.x;
		engine->updateCamPos(Point(screenmove.x,0));
	}
	if (engine->getMsePos().intY() >= engine->screenHeight - mouseThreshold){
		//engine->camera->y -= screenmove.y;
		engine->updateCamPos(Point(0,-screenmove.y));
	}
	if (engine->getMsePos().intY() <= mouseThreshold){
		//engine->camera->y += screenmove.x;
		engine->updateCamPos(Point(0,screenmove.y));
	}
}

void Players::addPlayer(Sprite *s){
	players.push_back(s);
}

