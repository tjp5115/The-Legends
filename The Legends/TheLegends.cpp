// TheLegends.cpp : Defines the entry point for the console application.
//

#include "Cmain.h"
// install Visual Leak Detector to use this header
// i currently have it set up to use the directory: C:\Program Files (x86)\Visual Leak Detector

//#include "vld.h"

int main(int argc, char* argv[])
{
	Cmain *cmain = new Cmain(800,600);
	
	cmain->GameLoop();
	delete cmain;
	return 0;
}
