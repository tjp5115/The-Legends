#pragma once
#include "TL_engine.h"
class CollisionRect
{
public:
	CollisionRect(void);
	CollisionRect(int x , int y, int w , int h);
	~CollisionRect();

	SDL_Rect getRect(){ return collisionRect; }
	void setRect(int x , int y, int w, int h);
	void setX(int x){ collisionRect.x = x + offset.x; }
	void setY(int y){ collisionRect.y = y + offset.y; }
	
private:
	Point offset;
	SDL_Rect collisionRect;
};

