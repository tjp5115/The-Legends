#include "mainCharacter.h"

mainCharacter::mainCharacter(TL_Engine *p_engine, Environment *p_environment)
{
	engine = p_engine;
	environment = p_environment;
	SPEED = 5.2f;
	follow = false;
	follow_point_x = *engine->mouseX;
	follow_point_y = *engine->mouseY;

	timeCheck = SDL_GetTicks();
	debugTime = SDL_GetTicks();
	distance = 0;
	stopAnimation = false;


	bob = new Sprite(engine, "data/tom.png", 300, 250, 130, 130, CollisionRect(168, 172, 60, 35));
	ping = new Sprite(engine, "data/movement/ping.png", 300, 250, 20, 20, CollisionRect());
	bob->setY(bob->getY());
	bob->setX(bob->getX());

	bob->setupAnimation(4, 4);
}


mainCharacter::~mainCharacter()
{
	delete bob;
}

void mainCharacter::draw(){
		bob->drawSteady();
		if ( (*engine->cameraY != int(follow_point_y)) && (*engine->cameraX != int(follow_point_x)) ){
			//ping->camera.x = *engine->cameraX - follow_point_x+500;
			//ping->camera.y = *engine->cameraY - follow_point_y+500;

			ping->drawPointer(mouseClickX,mouseClickY);

		}
}

void mainCharacter::updateAnimation(){
	float angle = atan2(follow_point_y - *engine->cameraY, follow_point_x - *engine->cameraX);
	angle = angle * (180 / 3.14) + 180;
	if (!stopAnimation){
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
}

void mainCharacter::updateControls(){

	if (engine->getMainEvent()->type == SDL_MOUSEBUTTONDOWN || engine->getMainEvent()->type == SDL_MOUSEMOTION){
		if (engine->getMainEvent()->button.button == SDL_BUTTON_LEFT){
			follow_point_x = *engine->cameraX - *engine->mouseX + 300;
			follow_point_y = *engine->cameraY - *engine->mouseY + 250;
			follow = true;
			mouseClickX = *engine->mouseX;
			mouseClickY = *engine->mouseY;
			if (debugTime + 500 < SDL_GetTicks()){
				std::cout << "MP_CAMERA:\t  X: " << *engine->cameraX << "\tY: " << *engine->cameraY << std::endl;
				std::cout << "MP_FOLLOW:\t  X: " << follow_point_x << "\tY: " << follow_point_y << std::endl;
				std::cout << "MP_MOUSE:\t X: " << *engine->mouseX << "\tY: " << *engine->mouseY << std::endl;
				std::cout << "DISTANCE: " << distance << std::endl;
				debugTime = SDL_GetTicks();
			}
		}
	}


	if (timeCheck + 7 < SDL_GetTicks() && follow){

		distance = getDistance(*engine->cameraX, *engine->cameraY, follow_point_x, follow_point_y);
		if (distance == 0){
			stopAnimation = true;
		}
		else{
			stopAnimation = false;
		}
		if (distance > 15){
			bool collide = false;
			std::vector<Tree*> trees = environment->getTrees();
			for (int i = 0; i < trees.size(); ++i){
				if (bob->isColliding( trees[i]->getTrunk()->getCollisionRect() ) ) {
					if (follow_point_x < *engine->cameraX){
						*engine->cameraX += 1;
					}
					if (follow_point_x > *engine->cameraX){
						*engine->cameraX -= 1;
					}
					if (follow_point_y < *engine->cameraY){
						*engine->cameraY += 1;
					}
					if (follow_point_y > *engine->cameraY){
						*engine->cameraY -= 1;
					}
					follow_point_x = *engine->cameraX;
					follow_point_y = *engine->cameraY;
					collide = true;
					stopAnimation = true;
				}
			}
			if (!collide){
				if (*engine->cameraY != int(follow_point_y)){
					*engine->cameraY = *engine->cameraY - (((*engine->cameraY - follow_point_y) / distance)*SPEED);
					mouseClickY = mouseClickY - (((*engine->cameraY - follow_point_y) / distance)*SPEED);
					;
				}
				if (*engine->cameraX != int(follow_point_x)){
					*engine->cameraX = *engine->cameraX - (((*engine->cameraX - follow_point_x) / distance)*SPEED);
					mouseClickX = mouseClickX - (((*engine->cameraX - follow_point_x) / distance)*SPEED);
				}
			}
		}
		timeCheck = SDL_GetTicks();
	}

}

void mainCharacter::update(){

	updateAnimation();
	updateControls();

}
float mainCharacter::getDistance(int x1, int y1, int x2, int y2){
	float diffx = x1 - x2;
	float diffy = y1 - y2;

	return (float)sqrt((diffx * diffx) + (diffy * diffy));
}