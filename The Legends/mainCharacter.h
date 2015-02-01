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
	Point *position;
	Point follow;
	Point moveDistance;

	void mainCharacter::updateAnimation();
	void mainCharacter::updateControls();

	Environment *environment;
	float SPEED;
	float distance;

	int timeCheck;

	bool collide;
	bool *following;

	void moveCharacter(Point dist);
	void collision();
};

