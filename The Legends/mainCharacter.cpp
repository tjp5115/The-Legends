#include "mainCharacter.h"

mainCharacter::mainCharacter(TL_Engine *p_engine, Environment *p_environment)
{		
	engine = p_engine;
	environment = p_environment;
	SPEED = 5.2f;
	following = false;
	follow = *engine->mouse;
	moveDistance.y = 0;
	moveDistance.x = 0;
	distance = 0;
	collide = false;
	bob = new Sprite(engine, "data/tom.png", 300, 250, 130, 130, CollisionRect(168, 172, 60, 35));
	ping = new Sprite(engine, "data/movement/ping.png", 300, 250, 20, 20, CollisionRect());
	bob->setY(bob->getY());
	bob->setX(bob->getX());

	bob->setupAnimation(4, 4);
}


mainCharacter::~mainCharacter()
{
	delete bob;
	delete ping;
}

void mainCharacter::draw(){
		bob->drawSteady();
		if ( following ){
			ping->drawPointer(mouseClick.x - ping->getPositionRect().h/2,mouseClick.y - ping->getPositionRect().h/2);
		}
}

void mainCharacter::updateAnimation(){
	float angle = atan2(follow.y - engine->camera->y, follow.x - engine->camera->x);
	angle = angle * (180 / 3.14) + 180;
	if (angle > 225 && angle <= 315){
		//up
		if (distance > 15){
			bob->playAnimation(0, 3, 3, 300);
		}
		else{
			bob->playAnimation(1, 1, 3, 300);
		}
	}
	else if ((angle <= 360 && angle > 315) || (angle >= 0 && angle <= 45)) {
		//right
		if (distance > 15){
			bob->playAnimation(0, 3, 2, 300);
		}
		else{
			bob->playAnimation(1, 1, 2, 300);
		}
	}
	else if (angle > 45 && angle <= 135){
		//down
		if (distance > 15){
			bob->playAnimation(0, 3, 0, 300);
		}
		else{
			bob->playAnimation(1, 1, 0, 300);
		}
	}
	else if (angle > 135 && angle <= 225){
		//left
		if (distance > 15){
			bob->playAnimation(0, 3, 1, 300);
		}
		else{
			bob->playAnimation(1, 1, 1, 300);
		}
	}
}

void mainCharacter::updateControls(){

	if (engine->mouseClickLeft()){
		follow.x = engine->camera->x  - engine->mouse->x + bob->getX() + bob->getWidth()/2 ;
		follow.y = engine->camera->y - engine->mouse->y + bob->getY() + bob->getHeight() ;
		following = true;
		mouseClick.x = engine->mouse->x;
		mouseClick.y = engine->mouse->y;
		distance = engine->getDistance(*engine->camera, follow);
		moveDistance.x = ((engine->camera->x  - follow.x) / distance)*SPEED;
		moveDistance.y = ((engine->camera->y - follow.y) / distance)*SPEED;

	}
	if (timeCheck + 7 < SDL_GetTicks() && following){
		collision();
		distance = engine->getDistance(*engine->camera, follow);
		if (distance > 4){
			moveCharacter(moveDistance);
		}
		else{
			engine->camera->x = follow.x;
			engine->camera->y = follow.y;
			/*
			Point temp;
			temp.x = engine->camera->x - follow.x;
			temp.y = engine->camera->y - follow.y;
			
			moveCharacter(temp);
			*/
			following = false;
		}
	timeCheck = SDL_GetTicks();
	}
}
void mainCharacter::collision(){
	collide = false;
	std::vector<Tree*> trees = environment->getTrees();
	for (int i = 0; i < trees.size(); ++i){
		if (bob->isColliding(trees[i]->getTrunk()->getCollisionRect())) {
			if (follow.x< engine->camera->x){
				engine->camera->x += 5;
			}
			if (follow.x> engine->camera->x ){
				engine->camera->x -= 5;
			}
			if (follow.y< engine->camera->y){
				engine->camera->y += 5;
			}
			if (follow.y> engine->camera->y){
				engine->camera->y -= 5;
			}
			following = false;
			collide = true;
			follow = *engine->camera;
		}
	}
}

void mainCharacter::moveCharacter(Point dist){
	if (!collide){
		if (engine->camera->intX() != follow.intX()){
			engine->camera->x -= moveDistance.x;
			if (!engine->mouseClickLeft()){
				mouseClick.x -= moveDistance.x;
			}
		}
		if (engine->camera->intY() != follow.intY()){
			engine->camera->y -= moveDistance.y;
			if (!engine->mouseClickLeft()){
				mouseClick.y -= moveDistance.y;
			}
		}
	}
}
void mainCharacter::update(){
	updateAnimation();
	updateControls();
	if (engine->debug){
		string s = "followX:    " + to_string(follow.x) + "    followY     " + to_string(follow.y);
		engine->addDebugText(s);
		s = "mouseClickX:    " + to_string(mouseClick.x) + "    mouseClickY     " + to_string(mouseClick.y);
		engine->addDebugText(s);
		s = "distance:    " + to_string(distance);
		engine->addDebugText(s);
		s = "moveDistX:    " + to_string(moveDistance.x) + "    moveDistY     " + to_string(moveDistance.y);	
		engine->addDebugText(s);
	}
}
