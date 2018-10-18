#include "point2i.h"

Point2i::Point2i()
{
	x = y = 0;
}

Point2i::Point2i(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool Point2i::operator==(const Point2i &point) const
{
	return (x == point.x && y == point.y);
}

bool Point2i::operator!=(const Point2i &point) const
{
	return (x != point.x || y != point.y);
}
