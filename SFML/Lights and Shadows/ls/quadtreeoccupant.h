#pragma once
#include "quadtreenode.h"
#include "aabb.h"

namespace qdt
{
	class QuadTreeOccupant
	{
		class QuadTreeNode* node;
		class QuadTree* tree;

	protected:
		AABB aabb;

	public:
		QuadTreeOccupant();
		void update();
		void remove();
		const AABB &getAABB();

		friend class QuadTreeNode;
		friend class QuadTree;
	};
}