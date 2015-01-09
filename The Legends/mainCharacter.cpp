#include "mainCharacter.h"

mainCharacter::mainCharacter(TL_Engine *p_engine, Environment *p_environment)
{		
	engine = p_engine;
	environment = p_environment;
	SPEED = 5.2f;
	following = false;
	follow = *engine->mouse;

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
	delete ping;
}

void mainCharacter::draw(){
		bob->drawSteady();
		if (debugTime + 2000 < SDL_GetTicks()){
			std::cout << "DEFAULT POINT OUT" << std::endl;
			std::cout << "MP_CAMERA:\t  X: " << engine->cameraX() << "\tY: " << engine->cameraY() << std::endl;
			std::cout << "MP_FOLLOW:\t  X: " << follow.x << "\tY: " << follow.y << std::endl;
			std::cout << "MP_MOUSE:\t X: " << engine->mouseX() << "\tY: " << engine->mouseY() << std::endl;
			std::cout << "DISTANCE: " << distance << std::endl;
			debugTime = SDL_GetTicks();
		}
		if ( (engine->camera->intY() != follow.intY()) && (engine->camera->intX() != follow.intX()) ) {
			//ping->camera.x = *engine->cameraX - follow_point_x+500;
			//ping->camera.y = *engine->cameraY - follow_point_y+500;

			ping->drawPointer(mouseClickX,mouseClickY);


		}
}

void mainCharacter::updateAnimation(){
	float angle = atan2(follow.y - engine->camera->y, follow.x - engine->camera->x);
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

	if (engine->mouseClickLeft()){
		follow.x = engine->cameraX() - engine->mouseX()  + 365;
		follow.y = engine->cameraY() - engine->mouseY() + 380;
		following = true;
		mouseClickX = engine->mouseX();
		mouseClickY = engine->mouseY();
		if (debugTime + 500 < SDL_GetTicks()){
			std::cout << "Click POINT OUT" << std::endl;
			std::cout << "MP_CAMERA:\t  X: " << engine->cameraX() << "\tY: " << engine->cameraY() << std::endl;
			std::cout << "MP_FOLLOW:\t  X: " << follow.x << "\tY: " << follow.y << std::endl;
			std::cout << "MP_MOUSE:\t X: " << engine->mouseX() << "\tY: " << engine->mouseY() << std::endl;
			debugTime = SDL_GetTicks();
		}
	}
	if (timeCheck + 7 < SDL_GetTicks() && following){

		distance = engine->getDistance(*engine->camera, follow);
		if (distance < 1){
			stopAnimation = true;
		}
		else{
			stopAnimation = false;
		}
		if (distance > 0){
			bool collide = false;
			std::vector<Tree*> trees = environment->getTrees();
			for (int i = 0; i < trees.size(); ++i){
				if (bob->isColliding( trees[i]->getTrunk()->getCollisionRect() ) ) {
					if (follow.x< engine->cameraX()){
						engine->camera->x += 1;
					}
					if (follow.x> engine->cameraX()){
						engine->camera->x -= 1;
					}
					if (follow.y< engine->cameraY()){
						engine->camera->y += 1;
					}
					if (follow.y> engine->cameraY()){
						engine->camera->y -= 1;
					}
					follow.x = engine->cameraX();
					follow.y = engine->cameraY();
					collide = true;
					stopAnimation = true;
				}
			}
			if (!collide){
				if (engine->camera->intY() != follow.intY()){
					engine->camera->y = engine->cameraY() - (((engine->cameraY() - follow.y) / distance)*SPEED);
					mouseClickY = mouseClickY - (((engine->cameraY() - follow.y) / distance)*SPEED);
				}
				if (engine->camera->intX() != follow.intX()){
					engine->camera->x = engine->cameraX()- (((engine->cameraX() - follow.x) / distance)*SPEED);
					mouseClickX = mouseClickX - (((engine->cameraX() - follow.x) / distance)*SPEED);
				}
			}
			else{

			}
		}
		timeCheck = SDL_GetTicks();
	}
	
}

void mainCharacter::update(){

	updateAnimation();
	updateControls();

}
