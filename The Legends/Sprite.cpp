#include "Sprite.h"

Sprite::Sprite(){
}
Sprite::Sprite(TL_Engine *p_engine, const char* FilePath, int x, int y, int w, int h,CollisionRect p_collisionRect)
{
	collisionRect = p_collisionRect;

	engine = p_engine;
	renderer = engine->getRenderer();
	image = NULL;
	collImg = NULL;
	image_height = h;
	image_width = w;
	image = IMG_LoadTexture(renderer, FilePath);

	collImg = IMG_LoadTexture(renderer, "data/debug/rect.png");

	if (image == NULL){
		std::cout << "Error loading image: " << FilePath<< std::endl;
	}
	if (collImg== NULL){
		std::cout << "Error loading image: data/debug/rect.png"<< std::endl;
	}
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_QueryTexture(image, NULL, NULL, &image_width, &image_height);

//	xPos = x;
//	yPos = y;

	crop.w = image_width;
	crop.h = image_height;

	origin.x -=rect.w / 2;
	origin.y -= rect.h - 10 ;

	amount_frame.x = 0;
	amount_frame.y = 0;

	camera.x = rect.x + engine->getCamPos().x;
	camera.y = rect.y + engine->getCamPos().y;
	camera.w = rect.w;
	camera.h = rect.h;

}

Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
	SDL_DestroyTexture(collImg);
}

void Sprite::setupAnimation(int x, int y){
	amount_frame.x = x;
	amount_frame.y = y;
}

void Sprite::playAnimation(int beginFrame, int endFrame, int row, float speed){
	if (animationDelay + speed < SDL_GetTicks()){
		if (endFrame <= currentFrame){
			currentFrame = beginFrame;
		}
		else{
			currentFrame++;
		}
		crop.x = currentFrame * image_width / amount_frame.x;
		crop.y = image_height / amount_frame.y * row;
		crop.w = image_width / amount_frame.x;
		crop.h = image_height / amount_frame.y;

		animationDelay = SDL_GetTicks();
	}
}

void Sprite::drawSteady(){
		SDL_RenderCopy(renderer, image, &crop, &camera);
		SDL_RenderCopy(renderer, collImg, NULL, &collisionRect.getRect());
}

void Sprite::draw(void){
	camera.x = rect.x + engine->getCamPos().x;
	camera.y = rect.y + engine->getCamPos().y;
	collisionRect.setX(rect.x + engine->getCamPos().x);
	collisionRect.setY(rect.y + engine->getCamPos().y);

	SDL_RenderCopy(renderer, image, &crop, &camera);
	SDL_RenderCopy(renderer, collImg, NULL,&collisionRect.getRect());
}
void Sprite::draw(Point p){
	//camera.x = rect.x + p.x;
	//camera.y = rect.y + p.y;
	camera.x = p.x;
	camera.y = p.y;
	collisionRect.setX(p.x);
	collisionRect.setY(p.y);

	SDL_RenderCopy(renderer, image, &crop, &camera);
	SDL_RenderCopy(renderer, collImg, NULL, &collisionRect.getRect());
}
/*
float Sprite::getX(){
//	return xPos;
}

float Sprite::getY(){
//	return yPos;
}

void Sprite::setX(float x){
	rect.x = int(x + origin_x);
//	xPos = x;
}
void Sprite::setY(float y){
	rect.y = int(y + origin_y);
//	yPos = y;
}
*/
void Sprite::setPosition(float x, float y){
	rect.x = (int)x;
	rect.y = (int)y;
//	xPos = x;
//	yPos = y;
}

float Sprite::getHeight(){
	return float(rect.h);
}
float Sprite::getWidth(){
	return float(rect.w);
}
void Sprite::setHeight(int h){
	rect.h = h;
}
void Sprite::setWidth(int w){
	rect.w = w;
}

bool Sprite::isColliding(CollisionRect r){
	return !(collisionRect.getRect().x + collisionRect.getRect().w < r.getRect().x ||
		collisionRect.getRect().y + collisionRect.getRect().h < r.getRect().y ||
		collisionRect.getRect().x > r.getRect().x + r.getRect().w ||
		collisionRect.getRect().y > r.getRect().y + r.getRect().h
		);
}
