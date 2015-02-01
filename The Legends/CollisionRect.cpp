#include "CollisionRect.h"


CollisionRect::CollisionRect(int x, int y , int w, int h)
{
	offset.x = x;
	offset.y = y;
	setRect(x, y, w, h);
}

CollisionRect::CollisionRect()
{
	offset.x = 0;
	offset.y = 0;
	setRect(0, 0, 0, 0);
}
CollisionRect::~CollisionRect()
{
}

void CollisionRect::setRect(int x, int y, int w, int h){
	collisionRect.x = x + offset.x;
	collisionRect.y = y + offset.y;
	collisionRect.w = w;
	collisionRect.h = h;
}