#include "staticquadtree.h"
#include <cassert>

namespace qdt
{
	StaticQuadTree::StaticQuadTree()
	{
		created = false;
	}

	StaticQuadTree::StaticQuadTree(const AABB &rootRegion)
	{
		root.reset(new QuadTreeNode(rootRegion, 0));
		created = true;
	}

	void StaticQuadTree::create(const AABB &rootRegion)
	{
		root.reset(new QuadTreeNode(rootRegion, 0));
		created = true;
	}

	void StaticQuadTree::add(QuadTreeOccupant* occupant)
	{
		assert(created);

		setQuadTree(occupant);

		// If the occupant fits in the root node
		if(root->getRegion().contains(occupant->getAABB()))
			root->add(occupant);
		else
			outsideRoot.insert(occupant);
	}

	void StaticQuadTree::clear()
	{
		root.reset();
		outsideRoot.clear();
		created = false;
	}

	bool StaticQuadTree::isCreated()
	{
		return created;
	}
}
