#pragma once
#include "CollisionRect.h"
#include "Environment.h"
#include "Sprite.h"
class mainCharacter : public Sprite
{
public:
	mainCharacter(TL_Engine *p_engine, Environment *p_environment, const char* FilePath, int x, int y, int h, int w, CollisionRect p_collisionRect);

	~mainCharacter();
	void update();
	void draw();
private:
	Environment *environment;
	float SPEED;
	Point follow;
	bool *following;
	float distance;
	bool collide;
	Point moveDistance;
	void moveCharacter(Point dist);
	void collision();
	void mainCharacter::updateAnimation();
	void mainCharacter::updateControls();
	int timeCheck;
	Point *position;
};

