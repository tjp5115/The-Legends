#pragma once
class Point
{
public:
	Point(float p_x, float p_y);
	Point();
	~Point();
	float x;
	float y;
	int intX(){ return int(x); }
	int intY(){ return int(y); }
	void set(float p_x, float p_y);
	void addPlayerPosition(Point * p);
	void updatePlayerPosition(Point p);
};

