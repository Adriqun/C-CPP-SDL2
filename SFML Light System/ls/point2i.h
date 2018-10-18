#pragma once

struct Point2i
{
	int x, y;

	Point2i(int x, int y);
	Point2i();
	bool operator==(const Point2i &point) const;
	bool operator!=(const Point2i &point) const;
};