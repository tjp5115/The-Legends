#pragma once
#include "Sprite.h"
#include "CollisionRect.h"
#include "Tree.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
class Environment 
{
public:
	Environment(TL_Engine *p_engine);
	~Environment();

	void drawBack();
	void drawFront();

	void update();

	void loadEnvFromFile();
	void saveEnvFile();
	enum ModeType{
		PLAY,
		EDIT	
	};
	enum EnvType{
		ENV_NONE,
		ENV_FOREST,
	};

	std::vector<Tree*> getTrees(){ return trees; }
private:
	TL_Engine *engine;
	std::vector<Sprite*> grass;
	std::vector<Sprite*> border;
	Sprite *corner[4];
	bool onePressed;
	int game_mode;
	int env_type;
	std::vector<Tree*> trees;
	
};

