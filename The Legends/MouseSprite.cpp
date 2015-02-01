#include "MouseSprite.h"


MouseSprite::MouseSprite(TL_Engine *p_engine, bool *p_character_moving, const char* FilePath, int x, int y, int h, int w, CollisionRect p_collisionRect) :
Sprite(p_engine, FilePath, x, y, h, w, p_collisionRect)
{
	character_moving = p_character_moving;
}


MouseSprite::~MouseSprite()
{
}
void MouseSprite::draw(){
	if (character_moving){
		camera.x = engine->getCamPos().x - getPositionRect().w / 2;
		camera.y = engine->getCamPos().y - getPositionRect().h / 2;
		collisionRect.setX(rect.x + engine->getCamPos().x);
		collisionRect.setY(rect.y + engine->getCamPos().y);

		Sprite::drawSteady();
	}
}
