#define _SCL_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <time.h>
#include <math.h>
#include <boost/foreach.hpp>


#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

// bg, bgm, bgi
namespace bg = boost::geometry;
namespace bgm = bg::model;
namespace bgi = bg::index;

// Point
typedef bgm::point<float, 2, bg::cs::cartesian> Point;

// Box
typedef bgm::box<Point> Box;

// BoxID
typedef std::pair<Box, int> BoxID;

// RTree
typedef bgi::rtree<BoxID, bgi::quadratic<16>> Tree;


int temp = 0;
float start = 0, end = 0;
int size = 10000;

struct Rect
{
	float l, r;
	float t, b;

	Rect(float, float, float, float);
	bool contains(Rect rect);
};

Rect::Rect(float l, float r, float t, float b)
{
	this->l = l;
	this->r = r;
	this->t = t;
	this->b = b;
}

bool Rect::contains(Rect rect)
{
	if (r < rect.l)			return false;
	else if(l > rect.r)		return false;
	else if (b > rect.t)	return false;
	else if (t < rect.b)	return false;

	return true;
}

int main()
{
	srand(static_cast <unsigned> (time(NULL)));
	std::cout.precision(17);


	Tree tree;
	std::vector<Rect> rects;

	start = clock();
	for (unsigned i = 0; i < size; ++i)
	{
		float l = rand() % 100000;
		float r = l + 1000;
		float t = rand() % 100000;
		float b = t + 1000;

		Rect rect(l, r, t, b);
		rects.push_back(rect);
	}
	end = clock();
	std::cout << "Vector inserting test: it took " << ((float)end - start) / CLOCKS_PER_SEC << "seconds." << std::endl;
	start = clock();
	for (unsigned i = 0; i < rects.size(); ++i)
	{
		Box box(Point(rects[i].l, rects[i].t), Point(rects[i].r, rects[i].b));
		tree.insert(std::make_pair(box, i));
	}
	end = clock();
	std::cout << "Tree inserting test: it took " << ((float)end - start) / CLOCKS_PER_SEC << "seconds." << std::endl;




	Box window_box(Point(250, 250), Point(500, 500));
	Rect window_rect(250, 250, 500, 500);
	int t1 = 1000, t2 = 1000;
	// Test tree
	start = clock();
	while(--t1)
	{
		// find values intersecting some area defined by a box
		std::vector<BoxID> result;
		tree.query(bgi::intersects(window_box), std::back_inserter(result));
	
		// find 5 nearest values to a point
		// std::vector<value> result_n;
		// rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));

		// std::cout << "spatial query result:" << std::endl;
		BOOST_FOREACH(BoxID const& v, result)
		{
			// std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;
			// std::cout << "x: " << bg::get<bg::min_corner, 0>(v.first) << std::endl;
			// std::cout << "y: " << bg::get<bg::min_corner, 1>(v.first) << std::endl;
			// std::cout << "x+w: " << bg::get<bg::max_corner, 0>(v.first) << std::endl;
			// std::cout << "y+h: " << bg::get<bg::max_corner, 1>(v.first) << std::endl;
			// std::cout << std::endl;
			temp = bg::get<bg::min_corner, 0>(v.first);
		}
	}
	end = clock();
	std::cout << "Tree collision test: it took " << ((float)end - start) / CLOCKS_PER_SEC << "seconds." << std::endl;


	// Test array
	start = clock();
	while (--t2)
		for (unsigned i = 0; i < rects.size(); ++i)
		{
			if (rects[i].contains(window_rect))
			{
				temp = rects[i].l;
			}
		}
	end = clock();
	std::cout << "Array collision test: it took " << ((float)end - start) / CLOCKS_PER_SEC << "seconds." << std::endl;


	// std::cout << "knn query point:" << std::endl;
	// std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
	// std::cout << "knn query result:" << std::endl;
	// BOOST_FOREACH(value const& v, result_n)
		// std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;

	return 0;
}