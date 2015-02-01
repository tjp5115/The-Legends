#include "mainCharacter.h"

mainCharacter::mainCharacter(TL_Engine *p_engine,Environment *p_environment, const char* FilePath, int x, int y, int h, int w, CollisionRect p_collisionRect)	:
Sprite(p_engine, FilePath, x, y, h, w, p_collisionRect)
{
	environment = p_environment;
	SPEED = 5.2f;
	following = (bool*)malloc(sizeof(bool));
	*following = false;
	follow = Point(0,0);
	moveDistance.y = 0;
	moveDistance.x = 0;
	distance = 0;
	collide = false;
	
	position = new Point(250,400);

	timeCheck = SDL_GetTicks();
	setupAnimation(4, 4);
}


mainCharacter::~mainCharacter()
{
	free(following);
}

void mainCharacter::draw(){
	rect.x = position->x;
	rect.y = position->y;
	//Sprite::draw(*position);
	Sprite::draw();

}

void mainCharacter::updateAnimation(){
	float angle = atan2(follow.y - engine->camera->y, follow.x - engine->camera->x);
	angle = angle * (180 / 3.14) + 180;
	if (angle > 225 && angle <= 315){
		//up
		if (distance > 15){
			playAnimation(0, 3, 3, 300);
		}
		else{
			playAnimation(1, 1, 3, 300);
		}
	}
	else if ((angle <= 360 && angle > 315) || (angle >= 0 && angle <= 45)) {
		//right
		if (distance > 15){
			playAnimation(0, 3, 2, 300);
		}
		else{
			playAnimation(1, 1, 2, 300);
		}
	}
	else if (angle > 45 && angle <= 135){
		//down
		if (distance > 15){
			playAnimation(0, 3, 0, 300);
		}
		else{
			playAnimation(1, 1, 0, 300);
		}
	}
	else if (angle > 135 && angle <= 225){
		//left
		if (distance > 15){
			playAnimation(0, 3, 1, 300);
		}
		else{
			playAnimation(1, 1, 1, 300);
		}
	}
}

void mainCharacter::updateControls(){

	if (engine->mouseClickLeft()){
		engine->mouseClick = *engine->mouse;
		//follow.x = position->x - engine->mouse->x + getWidth()/2 ;
		//follow.y = position->y - engine->mouse->y + getHeight() ;
		follow.x = engine->camera->x + engine->mouse->x - getWidth()/2;
		follow.y = engine->camera->y + engine->mouse->y - getHeight();
		
		*following = true;

		distance = engine->getDistance(*position, follow);
		moveDistance.x = ((position->x  - follow.x) / distance)*SPEED;
		moveDistance.y = ((position->y - follow.y) / distance)*SPEED;
	}
	if (timeCheck + 7 < SDL_GetTicks() && *following){
		collision();
		distance = engine->getDistance(*position, follow);
		if (distance > 4){
			moveCharacter(moveDistance);
		}
		else{
			*position = follow;
			/*
			Point temp;
			temp.x = engine->camera->x - follow.x;
			temp.y = engine->camera->y - follow.y;
			
			moveCharacter(temp);
			*/
			*following = false;
		}
		timeCheck = SDL_GetTicks();
	}
}

void mainCharacter::collision(){
	collide = false;
	std::vector<Tree*> trees = environment->getTrees();
	for (int i = 0; i < trees.size(); ++i){
		if (isColliding(trees[i]->getTrunk()->getCollisionRect())) {
			if (follow.x< engine->camera->x){
				position->x += 5;
			}
			if (follow.x> engine->camera->x ){
				position->x -= 5;
			}
			if (follow.y< engine->camera->y){
				position->y += 5;
			}
			if (follow.y> engine->camera->y){
				position->y -= 5;
			}
			*following = false;
			collide = true;
			//follow = *engine->camera;
		}
	}
}

void mainCharacter::moveCharacter(Point dist){
	if (!collide){
		if (position->intX() != follow.intX()){
			position->x -= dist.x;
			if (!engine->mouseClickLeft()){
				engine->mouseClick.x -= dist.x;
			}
		}
		if (position->intY() != follow.intY()){
			position->y -= dist.y;
			if (!engine->mouseClickLeft()){
				engine->mouseClick.y -= dist.y;
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
		s = "mouseClickX:    " + to_string(engine->mouseClick.x) + "    mouseClickY     " + to_string(engine->mouseClick.y);
		engine->addDebugText(s);
		s = "distance:    " + to_string(distance);
		engine->addDebugText(s);
		s = "moveDistX:    " + to_string(moveDistance.x) + "    moveDistY     " + to_string(moveDistance.y);	
		engine->addDebugText(s);
		s = "playerPosX:    " + to_string(position->x) + "    playerPosY     " + to_string(position->y);
		engine->addDebugText(s);
	}
}
