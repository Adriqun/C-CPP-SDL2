#include "quadtreeoccupant.h"
#include "quadtree.h"
#include "vec2f.h"
#include <cassert>

namespace qdt
{
	QuadTreeOccupant::QuadTreeOccupant()
	{
		node = nullptr;
		tree = nullptr;
		aabb = AABB(Vec2f(0.0f, 0.0f), Vec2f(1.0f, 1.0f));
	}

	void QuadTreeOccupant::update()
	{
		if(!tree)
			return;

		if(!node)
		{
			// If fits in the root now, add it
			QuadTreeNode* root = tree->root.get();

			if(root->region.contains(aabb))
			{
				// Remove from outside root and add to tree
				tree->outsideRoot.erase(this);

				root->add(this);
			}
		}
		else
			node->update(this);
	}

	void QuadTreeOccupant::remove()
	{
		if (!node)
		{
			// Not in a node, should be outside root then
			assert(tree);

			tree->outsideRoot.erase(this);

			tree->onRemoval();
		}
		else
			node->remove(this);
	}

	const AABB &QuadTreeOccupant::getAABB()
	{
		return aabb;
	}
}
