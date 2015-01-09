#pragma once
#include "TL_Engine.h"
#include <vector>
class Debug
{
public:
	Debug(TL_Engine *p_engine);
	~Debug();
	void draw();
	void addText(const char* txt);
	void addText(std::vector<std::string> txt);
	void clear();
private:
	TL_Engine *engine;
	SDL_Color White;
	int fontSize;
	typedef struct{
		SDL_Texture* message; 
		SDL_Rect rect; 
		SDL_Surface *surface;
	}text;
	std::vector<text> debug_out;
	TTF_Font* Sans;
};

