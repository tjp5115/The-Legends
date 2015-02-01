#pragma once
#include "TL_Engine.h"
#include "CollisionRect.h"
class Sprite
{
public:
	Sprite(TL_Engine *p_engine, const char* FilePath, int x, int y, int h, int w, CollisionRect p_collisionRect);
	Sprite();
	~Sprite();

	void draw();
	
//	float getX();
//	float getY();
	SDL_Rect camera;
//	void setX(float x);
//	void setY(float y);

	void setPosition(float x, float y);

	void setOrigin(float x, float y);

	float getWidth();
	float getHeight();

	void setWidth(int w);
	void setHeight(int h);
	void playAnimation(int beginFrame, int endFrame, int row, float speed);
	void setupAnimation(int x, int y);

	void draw(Point p);
	void drawSteady();
	
	void movePos();
	
	bool isColliding(CollisionRect theCollider);
	CollisionRect getCollisionRect(){ return collisionRect; }
	
	SDL_Rect getPositionRect(){ return rect; }
protected:
	TL_Engine *engine;
	CollisionRect collisionRect;
	SDL_Rect rect;
private:
	Point origin;
	Point amount_frame;

	int image_height;
	int currentFrame;
	int animationDelay;
	int image_width;

	SDL_Renderer *renderer;
	SDL_Rect crop;
	SDL_Texture* image;
	SDL_Texture* collImg;
};

