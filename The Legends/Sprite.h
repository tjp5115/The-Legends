#pragma once
#include "TL_Engine.h"
#include "CollisionRect.h"
class Sprite
{
public:
	Sprite(TL_Engine *p_engine, const char* FilePath, int x, int y, int h, int w, CollisionRect p_collisionRect);
	~Sprite();

	void draw();
	
	float getX();
	float getY();
	SDL_Rect camera;
	void setX(float x);
	void setY(float y);

	void setPosition(float x, float y);

	void setOrigin(float x, float y);

	float getWidth();
	float getHeight();

	void setWidth(int w);
	void setHeight(int h);
	void playAnimation(int beginFrame, int endFrame, int row, float speed);
	void setupAnimation(int x, int y);

	CollisionRect getCollisionRext(){ return collisionRect; }

	void drawSteady();

	bool isColliding(CollisionRect theCollider);

	CollisionRect getCollisionRect(){ return collisionRect; }
	void drawPointer(int mouseClickX, int mouseClickY);
	SDL_Rect getPositionRext(){ return rect; }
private:
	TL_Engine *engine;
	SDL_Renderer *renderer;

	CollisionRect collisionRect;

	float origin_x;
	float origin_y;
	float xPos;
	float yPos;

	int image_width;
	int image_height;

	int amount_frame_x;
	int amount_frame_y;

	int currentFrame;
	int animationDelay;
	SDL_Rect crop;
	SDL_Texture* image;
	SDL_Texture* collImg;

	SDL_Rect rect;

};

