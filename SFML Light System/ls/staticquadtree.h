#pragma once
#include "quadtree.h"

namespace qdt
{
	class StaticQuadTree : public QuadTree
	{
	private:
		bool created;

	public:
		StaticQuadTree();
		StaticQuadTree(const AABB &rootRegion);

		void create(const AABB &rootRegion);
		void add(QuadTreeOccupant* occupant);
		void clear();
		bool isCreated();
	};
}