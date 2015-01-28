#include "Point.h"


Point::Point(float p_x, float p_y)
{
	x = p_x;
	y = p_y;
}

Point::Point()
{
	x = 0;
	y = 0;
}
Point::~Point()
{
}void Point::set(float p_x, float p_y){
	x = p_x;
	y = p_y; 
}
