#pragma once
#include "Sprite.h"
#include "Tree.h"
#include "CollisionRect.h"
#include "Environment.h"
#include <vector>


class mainCharacter
{
public:
	mainCharacter(TL_Engine *p_engine, Environment *p_environment);
	~mainCharacter();
	void update();
	void draw();
private:
	Point mouseClick;
	TL_Engine *engine;
	Environment *environment;
	float SPEED;
	Sprite *bob;
	Sprite *ping;
	Point follow;
	bool following;
	float distance;
	bool collide;
	Point moveDistance;
	void moveCharacter(Point dist);
	void collision();
	void mainCharacter::updateAnimation();
	void mainCharacter::updateControls();
	int timeCheck;
};

