#include "Cmain.h"


Cmain::Cmain(int passed_screenWidth, int passed_screenHeight)
{
	engine = NULL; 
	engine = new TL_Engine(passed_screenWidth, passed_screenHeight);

	players = new Players(engine);


	forestArea = NULL;
	forestArea = new Environment(engine);
	
	debug = new Debug(engine);
	bob = NULL;
	bob = new mainCharacter(engine, "data/tom.png", 300, 250, 130, 130, CollisionRect(0, 0, 60, 35));

	players->addPlayer(bob);
	//SDL_SetRelativeMouseMode(SDL_TRUE);
}


Cmain::~Cmain()
{
	delete engine;
	delete bob;
	delete debug;
	delete forestArea;
}


void Cmain::GameLoop(void){
	while (!engine->quit && engine->getMainEvent()->type != SDL_QUIT){
		//perform the begining loop functions
		engine->update_begin();
		if (debug){
			debug->clear();
		}
		//draw sprites
		forestArea->drawBack();
		players->update();
		bob->draw();
		bob->update();
		forestArea->drawFront();
		forestArea->update();
		if (engine->debug){
			engine->updateDebug();
			debug->addText(engine->debugText);
			debug->draw();
		}
		//run the end main loop routines
		engine->update_end();

	}
}


