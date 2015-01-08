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

	float getDistance(int x1, int y1, int x2, int y2);



	void update();
	void draw();
private:
	int mouseClickX;
	int mouseClickY;
	TL_Engine *engine;
	Environment *environment;
	float SPEED;
	Sprite *bob;
	Sprite *ping;
	int follow_point_x;
	int follow_point_y;
	bool follow;
	bool stopAnimation;
	int timeCheck;
	float distance;

	int debugTime;


	void mainCharacter::updateAnimation();
	void mainCharacter::updateControls();
};

