#pragma once
#include "quadtreenode.h"
#include "quadtreeoccupant.h"
#include <unordered_set>
#include <memory>

namespace qdt
{
	// Base class for dynamic and static QuadTree types
	class QuadTree
	{
	protected:
		std::unordered_set<QuadTreeOccupant*> outsideRoot;
		std::unique_ptr<QuadTreeNode> root;

		// Called whenever something is removed, an action can be defined by derived classes
		// Defaults to doing nothing
		virtual void onRemoval();

		void setQuadTree(QuadTreeOccupant* occupant);

	public:
		virtual void add(QuadTreeOccupant* occupant) = 0;

		void queryRegion(const AABB &region, std::vector<QuadTreeOccupant*> &result);

		void debugRender();

		friend class QuadTreeNode;
		friend class QuadTreeOccupant;
	};
}