#pragma once
#include "constructs.h"
#include "quadtree.h"
#include <SFML/OpenGL.hpp>
#include <vector>

namespace ls
{
	class ConvexHull : public qdt::QuadTreeOccupant
	{	
		bool aabbCalculated;
		Vec2f worldCenter;
		bool updateRequired;
		bool render;
		std::vector<Vec2f> normals;

	public:
		std::vector<Vec2f> vertices;
		float transparency;
		bool renderLightOverHull;

		ConvexHull();

		void centerHull();
		bool loadShape(std::string filename);
		Vec2f getWorldVertex(unsigned int index) const;

		void calculateAABB();
		void calculateNormals();

		void renderHull(float depth);
		bool hasCalculatedAABB() const;

		void setWorldCenter(const Vec2f &newCenter);
		void incWorldCenter(const Vec2f &increment);

		Vec2f getWorldCenter() const;
		bool pointInsideHull(const Vec2f &point);
		void debugDraw();
		
		friend class LightSystem;
	};
}