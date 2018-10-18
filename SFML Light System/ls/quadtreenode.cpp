#include "quadtreenode.h"
#include "quadtree.h"
#include <cassert>

namespace qdt
{
	// Defaults
	int QuadTreeNode::minNumOccupants = 3;
	int QuadTreeNode::maxNumOccupants = 6;
	int QuadTreeNode::maxNumLevels = 20;
	float QuadTreeNode::oversizeMultiplier = 1.2f;

	QuadTreeNode::QuadTreeNode()
	{
		hasChildren = false;
		numOccupantsBelow = 0;
	}

	QuadTreeNode::QuadTreeNode(const AABB &region, int level, QuadTreeNode* parent, QuadTree* tree)
	{
		this->region = region;
		this->level = level;
		this->parent = parent;
		this->tree = tree;
		hasChildren = false;
		numOccupantsBelow = 0;
	}

	QuadTreeNode::~QuadTreeNode()
	{
		if(hasChildren)
			destroyChildren();
	}

	void QuadTreeNode::create(const AABB &region, int level, QuadTreeNode* parent, QuadTree* tree)
	{
		this->region = region;
		this->level = level;
		this->parent = parent;
		this->tree = tree;
	}

	inline QuadTreeNode* QuadTreeNode::getChild(const Point2i position)
	{
		return &(*children)[position.x][position.y];
	}

	void QuadTreeNode::getPossibleOccupantPosition(QuadTreeOccupant* occupant, Point2i &point)
	{
		// Compare the center of the AABB of the occupant to that of this node to determine
		// which child it may (possibly, not certainly) fit in
		const Vec2f &occupantCenter(occupant->aabb.getCenter());
		const Vec2f &nodeRegionCenter(region.getCenter());

		point.x = occupantCenter.x > nodeRegionCenter.x ? 1 : 0;
		point.y = occupantCenter.y > nodeRegionCenter.y ? 1 : 0;
	}

	void QuadTreeNode::addToThisLevel(QuadTreeOccupant* occupant)
	{
		occupant->node = this;
		occupants.insert(occupant);
	}

	bool QuadTreeNode::addToChildren(QuadTreeOccupant* occupant)
	{
		assert(hasChildren);

		Point2i position;
		getPossibleOccupantPosition(occupant, position);

		QuadTreeNode* c = getChild(position);

		// See if the occupant fits in the child at the selected position
		if(c->region.contains(occupant->aabb))
		{
			// Fits, so can add to the child and finish
			c->add(occupant);
			return true;
		}

		return false;
	}

	void QuadTreeNode::partition()
	{
		assert(!hasChildren);

		const Vec2f &halfRegionDims(region.getHalfDims());
		const Vec2f &regionLowerBound(region.getLowerBound());
		const Vec2f &regionCenter(region.getCenter());

		int nextLowerLevel = level - 1;

		children = new std::vector<std::vector<QuadTreeNode>>();

		// Create the children nodes
		(*children).resize(2);

		for(int x = 0; x < 2; x++)
		{
			(*children)[x].resize(2);

			for(int y = 0; y < 2; y++)
			{
				Vec2f offset(x * halfRegionDims.x, y * halfRegionDims.y);

				AABB childAABB(regionLowerBound + offset, regionCenter + offset);

				childAABB.setHalfDims(childAABB.getHalfDims() * oversizeMultiplier);

				// Scale up AABB by the oversize multiplier
				(*children)[x][y].create(childAABB, nextLowerLevel, this, tree);
			}
		}

		hasChildren = true;
	}

	void QuadTreeNode::destroyChildren()
	{
		assert(hasChildren);
		delete children;
		hasChildren = false;
	}

	void QuadTreeNode::merge()
	{
		if(hasChildren)
		{
			// Place all occupants at lower levels into this node
			getOccupants(occupants);
			destroyChildren();
		}
	}

	void QuadTreeNode::getOccupants(std::unordered_set<QuadTreeOccupant*> &occupants)
	{
		// Iteratively parse subnodes in order to collect all occupants below this node
		std::list<QuadTreeNode*> open;

		open.push_back(this);

		while(!open.empty())
		{
			// Depth-first (results in less memory usage), remove objects from open list
			QuadTreeNode* current = open.back();
			open.pop_back();

			// Get occupants
			for(auto & it : current->occupants)
			{
				// Assign new node
				it->node = this;

				// Add to this node
				occupants.insert(it);
			}

			// If the node has children, add them to the open list
			if(current->hasChildren)
			{
				for(int x = 0; x < 2; x++)
					for(int y = 0; y < 2; y++)
						open.push_back(&(*current->children)[x][y]);
			}
		}
	}

	void QuadTreeNode::getAllOccupantsBelow(std::vector<QuadTreeOccupant*> &occupants)
	{
		// Iteratively parse subnodes in order to collect all occupants below this node
		std::list<QuadTreeNode*> open;

		open.push_back(this);

		while(!open.empty())
		{
			// Depth-first (results in less memory usage), remove objects from open list
			QuadTreeNode* current = open.back();
			open.pop_back();

			// Get occupants
			for (auto & it : current->occupants)
				occupants.push_back(it);	// Add to this node

			// If the node has children, add them to the open list
			if(current->hasChildren)
			{
				for(int x = 0; x < 2; x++)
					for(int y = 0; y < 2; y++)
						open.push_back(&(*current->children)[x][y]);
			}
		}
	}

	void QuadTreeNode::update(QuadTreeOccupant* occupant)
	{
		// Remove, may be re-added to this node later
		occupants.erase(occupant);

		// Propogate upwards, looking for a node that has room (the current one may still have room)
		QuadTreeNode* n = this;

		while(n)
		{
			n->numOccupantsBelow--;

			// If has room for 1 more, found a spot
			if(n->region.contains(occupant->aabb))
				break;

			n = n->parent;
		}

		// If no node that could contain the occupant was found, add to outside root set
		if(!n)
		{
			tree->outsideRoot.insert(occupant);
			occupant->node = NULL;
		}
		else // Add to the selected node
			n->add(occupant);
	}

	void QuadTreeNode::remove(QuadTreeOccupant* occupant)
	{
		assert(!occupants.empty());

		// Remove from node
		occupants.erase(occupant);

		// Propogate upwards, merging if there are enough occupants in the node
		QuadTreeNode* n = this;

		while(n)
		{
			n->numOccupantsBelow--;

			if(n->numOccupantsBelow >= minNumOccupants)
			{
				n->merge();
				break;
			}

			n = n->parent;
		}
	}

	void QuadTreeNode::add(QuadTreeOccupant* occupant)
	{
		numOccupantsBelow++;

		// See if the occupant fits into any children (if there are any)
		if(hasChildren)
		{
			if(addToChildren(occupant))
				return; // Fit, can stop
		}
		else
		{
			// Check if we need a new partition
			if(static_cast<signed>(occupants.size()) >= maxNumOccupants && level < maxNumLevels)
			{
				partition();

				if(addToChildren(occupant))
					return;
			}
		}

		// Did not fit in anywhere, add to this level, even if it goes over the maximum size
		addToThisLevel(occupant);
	}

	QuadTree* QuadTreeNode::getTree()
	{
		return tree;
	}

	const AABB &QuadTreeNode::getRegion()
	{
		return region;
	}
}
