#include "Tree.h"


Tree::Tree(TL_Engine *p_engine,int p_x,int p_y)
{		
	x = p_x;
	y = p_y;
	engine = NULL;
	engine = p_engine;

	trunk = new Sprite(engine, "data/environment/trunk.png", x, y, 43, 145,CollisionRect(0,100,43,45));
	crown = new Sprite(engine, "data/environment/crown.png", x-75, y-115, 183, 165, CollisionRect());
	//std::cout << "trunk collRect: "<<trunk->getCollisionRect().getRect().y << std::endl;
}


Tree::~Tree()
{
	delete trunk;
	delete crown;
}

void Tree::drawTrunk(){
	if (100 <= trunk->getPositionRext().y  - engine->cameraY()){
		trunk->draw();
	}
}

void Tree::drawCrown(){
	if (100 >= trunk->getPositionRext().y - engine->cameraY()){
		trunk->draw();
	}
	crown->draw();

}