#include "Environment.h"

//SDL_Setup *p_sdl_setup, int engine->screenWidth, int engine->screenHeight, float *passed_cameraX, float *passed_cameraY
Environment::Environment(TL_Engine *p_engine)
{
	engine = p_engine;
	int grassWidth= 130;
	int cWidth = 264;
	int cHeight= 275;
	onePressed = false;
		for (int i = 0; i < 4; ++i){
		int j = 0;

		for (j; j < 7; ++j){
			if (i == 0){
				border.push_back(new Sprite(engine, "data/environment/side_l.png", engine->screenWidth   * i - grassWidth, engine->screenHeight  * j, grassWidth, engine->screenHeight, CollisionRect()));
			}
			else if (i == 3){
				i++;
				border.push_back(new Sprite(engine, "data/environment/side_r.png", engine->screenWidth * i, engine->screenHeight * j, grassWidth, engine->screenHeight, CollisionRect()));
				--i;
			}
			if (j == 0){
				border.push_back(new Sprite(engine, "data/environment/side_u.png", engine->screenWidth * i, engine->screenHeight * j - grassWidth, engine->screenWidth, grassWidth, CollisionRect()));
			}else if (j == 6){
				j++;
				border.push_back(new Sprite(engine, "data/environment/side_b.png", engine->screenWidth * i, engine->screenHeight * j, engine->screenWidth, grassWidth, CollisionRect()));
				j--;
			}

			if (j == 0 & i == 0){
				corner[0] = new Sprite(engine, "data/environment/corner_tl.png", engine->screenWidth * i - grassWidth, engine->screenHeight * j - grassWidth, cWidth, cHeight,CollisionRect());
			}
			else if (j == 0 && i == 3){
				corner[1] = new Sprite(engine, "data/environment/corner_tr.png", engine->screenWidth * i + engine->screenWidth - cWidth/2, engine->screenHeight * j - cHeight/2, cWidth, cHeight,CollisionRect());
			}
			else if (j == 6 && i == 0){
				corner[2] = new Sprite(engine, "data/environment/corner_bl.png", engine->screenWidth * i - cWidth/2 , engine->screenHeight * j + engine->screenHeight-cHeight/2, cWidth, cHeight,CollisionRect());
			}
			else if (j == 6 && i == 3){
				corner[3] = new Sprite(engine, "data/environment/corner_br.png", engine->screenWidth * i + engine->screenWidth - cWidth/2, engine->screenHeight * j +engine->screenHeight- cWidth/2, cWidth, cHeight,CollisionRect());
			}

			grass.push_back( new Sprite(engine, "data/environment/grass.bmp", engine->screenWidth * i, engine->screenHeight * j, engine->screenWidth, engine->screenHeight,CollisionRect()) );
		}

	}
	game_mode = PLAY;
	env_type = ENV_NONE;

	loadEnvFromFile();
}


Environment::~Environment()
{
	for (std::vector<Sprite*>::iterator i = grass.begin(); i != grass.end(); ++i){
		delete (*i);
	}
	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i){
		delete (*i);
	}

	for (std::vector<Sprite*>::iterator i = border.begin(); i != border.end(); ++i){
		delete (*i);
	}
	for (int i = 0; i < 4; ++i) {
		delete corner[i];
	}

	border.clear();
	trees.clear();
	grass.clear();
}

void Environment::drawBack(){

	for (int i = 0; i < 4; ++i) {
		corner[i]->draw();
	}
	for (std::vector<Sprite*>::iterator i = grass.begin(); i != grass.end(); ++i){
		(*i)->draw();
	}

	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i){
		(*i)->drawTrunk();
	}

	for (std::vector<Sprite*>::iterator i = border.begin(); i != border.end(); ++i){
		(*i)->draw();
	}
}

void Environment::drawFront(){
	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i){
		(*i)->drawCrown();
	}

}

void Environment::update(){
	if (game_mode == EDIT){
		if (engine->getMainEvent()->type == SDL_KEYDOWN){
			if (!onePressed && engine->getMainEvent()->key.keysym.sym == SDLK_F1){
				trees.push_back(new Tree(engine, - engine->camera->intX() + 275, - engine->camera->intY() + 50));
				onePressed = true;
				//std::cout << "X: " << *cameraX << "\tY: " << *cameraY << std::endl;
			}
			else if (!onePressed && engine->getMainEvent()->key.keysym.sym == SDLK_F2){
				if (!trees.empty()){
					delete trees.back();
					trees.pop_back();
				}
				onePressed = true;
			}
			else if (!onePressed && engine->getMainEvent()->key.keysym.sym == SDLK_F11){
				saveEnvFile();
				onePressed = true;
			}
		}
		if (engine->getMainEvent()->type == SDL_KEYUP){
			if (onePressed && engine->getMainEvent()->key.keysym.sym == SDLK_F1){
				onePressed = false;
			}
			else if (onePressed && engine->getMainEvent()->key.keysym.sym == SDLK_F2){
				onePressed = false;
			}
			else if (onePressed && engine->getMainEvent()->key.keysym.sym == SDLK_F11){
				onePressed = false;
			}
		}
	}


		if (engine->getMainEvent()->type == SDL_KEYDOWN){
			if (!onePressed && engine->getMainEvent()->key.keysym.sym == SDLK_F12){
				if (game_mode == EDIT){
					game_mode = PLAY;
					std::cout << "Level Creation: OFF" << std::endl;
				}
				else{
					game_mode = EDIT;
					std::cout << "Level Creation: ON" << std::endl;
				}
				onePressed = true;
			}
		}
		if (engine->getMainEvent()->type == SDL_KEYUP){
			if (onePressed && engine->getMainEvent()->key.keysym.sym == SDLK_F12){
				onePressed = false;
			}
		}




}

void Environment::loadEnvFromFile(){
	std::ifstream file("data/stageLevel.txt");
	std::string line;
	if (file.is_open()){
		while (file.good()){
			std::getline(file, line);
			std::cout << line << std::endl;
			if (line == "=====BEGIN_FOREST====="){
				env_type = ENV_FOREST;
			}
			else if (line == "=====END_FOREST====="){
				env_type = ENV_NONE;
			}
			else{
				if (env_type == ENV_FOREST){
					std::string prevWord = "";
					std::istringstream iss(line);
					int temp_x, temp_y;
					while (iss){
						std::string word;
						iss >> word;
						if (prevWord == "x:"){
							temp_x = atoi(word.c_str());
						}
						else if (prevWord == "y:"){
							temp_y = atoi(word.c_str());
							trees.push_back(new Tree(engine, temp_x, temp_y));
						}
						prevWord = word;
					}
				}
			}
		}
	}
	else{
		std::cout << "Error loading environment" << std::endl;
	}
}

void Environment::saveEnvFile(){
	std::ofstream file;
	file.open("data/stageLevel.txt");
	file << "=====BEGIN_FOREST=====" << std::endl;
	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i){
		file << "x: " << (*i)->getX() << "\ty: " << (*i)->getY() <<std::endl;
	}
	file << "=====END_FOREST=====" << std::endl;
	file.close();

	std::cout << "LEVEL SAVED" << std::endl;
}

