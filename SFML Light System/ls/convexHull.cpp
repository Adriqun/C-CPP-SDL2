/*
Let There Be Light
Copyright (C) 2012 Eric Laukien

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
Update by Adrian Michalek 2018.10.18
- Some functions were updated and shorten.
- Some code were deleted due to regressions and depracations.
- Names of variables and functions were changed.
- Functionality stays the same.
*/

#include "convexHull.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <boost/lexical_cast.hpp>

namespace ls
{
	ConvexHull::ConvexHull()
	{
		aabbCalculated = false;
		worldCenter = Vec2f(0.0f, 0.0f);
		updateRequired = true;	// Remains true permanently unless user purposely changes it
		transparency = 1.0f;
		renderLightOverHull = true;
	}

	void ConvexHull::centerHull()
	{
		// Calculate the average of all of the vertices, and then
		// offset all of them to make this the new origin position (0,0)
		const unsigned int numVertices = vertices.size();

		Vec2f posSum(0.0f, 0.0f);
	
		for(unsigned int i = 0; i < numVertices; i++)
			posSum += vertices[i];

		Vec2f averagePos(posSum / static_cast<float>(numVertices));

		for(unsigned int i = 0; i < numVertices; i++)
			vertices[i] -= averagePos;
	}

	bool ConvexHull::loadShape(std::string filename)
	{
		std::ifstream load(filename);

		if(!load)
		{
			load.close();
			std::cout << "Could not load convex hull \"" << filename << "\"!" << std::endl;
			return false;
		}
		else
		{
			while(!load.eof())
			{
				std::string a, b;
				load >> a >> b;

				if(a.size() == 0 || b.size() == 0)
					break;

				float af = boost::lexical_cast<float>(a);
				float bf = boost::lexical_cast<float>(b);
				vertices.push_back(Vec2f(af, bf));
			}

			load.close();
		}

		centerHull();
		calculateNormals();
		return true;
	}

	Vec2f ConvexHull::getWorldVertex(unsigned int index) const
	{
		assert(index >= 0 && index < vertices.size());
		return Vec2f(vertices[index].x + worldCenter.x, vertices[index].y + worldCenter.y);
	}

	void ConvexHull::calculateNormals()
	{
		const unsigned int numVertices = vertices.size();

		if(normals.size() != numVertices)
			normals.resize(numVertices);

		for(unsigned int i = 0; i < numVertices; i++) // Dots are wrong
		{
			unsigned int index2 = i + 1;

			// Wrap
			if(index2 >= numVertices)
				index2 = 0;

			normals[i].x = -(vertices[index2].y - vertices[i].y);
			normals[i].y = vertices[index2].x - vertices[i].x;
		}
	}

	void ConvexHull::renderHull(float depth)
	{
		if(renderLightOverHull)
			return;

		glBegin(GL_TRIANGLE_FAN);

		const unsigned int numVertices = vertices.size();
	
		for(unsigned int i = 0; i < numVertices; i++)
		{
			Vec2f vPos(getWorldVertex(i));
			glVertex3f(vPos.x, vPos.y, depth);
		}

		glEnd();
	}

	void ConvexHull::calculateAABB()
	{
		assert(vertices.size() > 0);

		aabb.lowerBound = vertices[0];
		aabb.upperBound = aabb.lowerBound;

		for(unsigned int i = 0, size = vertices.size(); i < size; i++)
		{
			Vec2f* pos = &vertices[i];

			if(pos->x > aabb.upperBound.x)
				aabb.upperBound.x = pos->x;

			if(pos->y > aabb.upperBound.y)
				aabb.upperBound.y = pos->y;

			if(pos->x < aabb.lowerBound.x)
				aabb.lowerBound.x = pos->x;

			if(pos->y < aabb.lowerBound.y)
				aabb.lowerBound.y = pos->y;
		}

		aabb.calculateHalfDims();
		aabb.calculateCenter();
		aabbCalculated = true;
	}

	bool ConvexHull::hasCalculatedAABB() const
	{
		return aabbCalculated;
	}

	void ConvexHull::setWorldCenter(const Vec2f &newCenter)
	{
		worldCenter = newCenter;
		aabb.setCenter(worldCenter);
		update();
	}

	void ConvexHull::incWorldCenter(const Vec2f &increment)
	{
		worldCenter += increment;
		aabb.incCenter(increment);
		update();
	}

	Vec2f ConvexHull::getWorldCenter() const
	{
		return worldCenter;
	}

	bool ConvexHull::pointInsideHull(const Vec2f &point)
	{
		int sgn = 0;

		for(unsigned int i = 0, numVertices = vertices.size(); i < numVertices; i++)
		{
			int wrappedIndex = wrap(i + 1, numVertices);
			Vec2f currentVertex(getWorldVertex(i));
			Vec2f side(getWorldVertex(wrappedIndex) - currentVertex);
			Vec2f toPoint(point - currentVertex);

			float cpd = side.cross(toPoint);

			int cpdi = static_cast<int>(cpd / abs(cpd));

			if(sgn == 0)
				sgn = cpdi;
			else if(cpdi != sgn)
				return false;
		}

		return true;
	}

	void ConvexHull::debugDraw()
	{
		const unsigned int numVertices = vertices.size();

		glTranslatef(worldCenter.x, worldCenter.y, 0.0f);

		glBegin(GL_LINE_LOOP);

		for(unsigned int i = 0; i < numVertices; i++)
			glVertex2f(vertices[i].x, vertices[i].y);
	}
}
