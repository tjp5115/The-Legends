#include "Debug.h"

Debug::Debug(TL_Engine *p_engine)
{
	TTF_Init();
	engine = p_engine;
	fontSize = 14;
	White = { 255, 255, 255 };  
	Sans = TTF_OpenFont("data/font/sans.ttf", fontSize); 
	if (Sans == NULL){
		printf("Oh My Goodness, an error : %s", TTF_GetError());
	}
}


Debug::~Debug()
{
	delete Sans;
	for (std::vector<text>::iterator i = debug_out.begin(); i != debug_out.end(); ++i){
		SDL_DestroyTexture(i->message);
	}

}
void Debug::draw(){
	for (std::vector<text>::iterator i = debug_out.begin(); i != debug_out.end(); i++){
		SDL_RenderCopy(engine->getRenderer(), i->message, NULL, &i->rect);
	}
}
void Debug::addText(const char* txt){

	text t;
	int pos = debug_out.size();
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, txt, White);
	if (!surfaceMessage){
		printf("Oh My Goodness, an error : %s", TTF_GetError());
	}

	t.message = SDL_CreateTextureFromSurface(engine->getRenderer(), surfaceMessage); 
	if (t.message == 0){
		exit(0);
	}
	t.rect.x = 0;
	t.rect.y = pos*fontSize; 
	t.rect.w = 100; 
	t.rect.h = 14; 
	SDL_QueryTexture(t.message, NULL, NULL, &t.rect.w, &t.rect.h);

	debug_out.push_back(t);
}

void Debug::addText(std::vector<std::string> txt){
	const char*t;
	while (txt.size() > 0){
		t = txt.back().c_str();
		addText(t);
		txt.pop_back();
	}
}

void Debug::clear(){
	debug_out.clear();
}