// TheLegends.cpp : Defines the entry point for the console application.
//

#include "Cmain.h"

int main(int argc, char* argv[])
{
	Cmain *main = new Cmain(800,600);
	
	main->GameLoop();

	return 0;
}
