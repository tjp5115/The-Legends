#include "Cmain.h"


Cmain::Cmain(int passed_screenWidth, int passed_screenHeight)
{
	quit = false; 
	engine = new TL_Engine(&quit, passed_screenWidth, passed_screenHeight);

	forestArea = NULL;
	forestArea = new Environment(engine);


	bob = NULL;
	bob = new mainCharacter(engine,forestArea);

}


Cmain::~Cmain()
{
	delete engine;
	delete bob;
}


void Cmain::GameLoop(void){
	while (!quit && engine->getMainEvent()->type != SDL_QUIT){
		//perform the begining loop functions
		engine->update_begin();

		//draw sprites
		forestArea->drawBack();

		bob->draw();
		bob->update();
		forestArea->drawFront();
		forestArea->update();

		//run the end main loop routines
		engine->update_end();

	}
}


