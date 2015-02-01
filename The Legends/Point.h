#pragma once
class Point
{
public:
	/*******Member Fucntions*******/
	//Accessors
	Point(double p_x, double p_y);
	Point();
	~Point();
	double x;
	double y;
	int intX(){ return (int)x; }
	int intY(){ return (int)y; }
	void set(double p_x, double p_y){ x = p_x; y = p_y; }
	//Mutators

};

