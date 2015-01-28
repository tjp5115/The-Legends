#pragma once
#include "Sprite.h"
class MouseSprite : public Sprite
{
public:
	MouseSprite(TL_Engine *p_engine, bool *p_character_moving, const char* FilePath, int x, int y, int h, int w, CollisionRect p_collisionRect);
	~MouseSprite();
	void draw();
private:
	bool *character_moving;

};

