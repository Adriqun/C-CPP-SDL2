#include "quadtree.h"
#include "quadtreenode.h"
#include <SFML/OpenGL.hpp>
#include <list>

namespace qdt
{
	void QuadTree::onRemoval()
	{

	}

	void QuadTree::setQuadTree(QuadTreeOccupant* occupant)
	{
		occupant->tree = this;
	}

	void QuadTree::queryRegion(const AABB &region, std::vector<QuadTreeOccupant*> &result)
	{
		// Query outside root elements
		for(auto &it : outsideRoot)
		{
			QuadTreeOccupant* occupant = it;
			if(region.intersects(occupant->aabb))
			{
				// Intersects, add to list
				result.push_back(occupant);
			}
		}

		std::list<QuadTreeNode*> open;

		open.push_back(root.get());

		while(!open.empty())
		{
			// Depth-first (results in less memory usage), remove objects from open list
			QuadTreeNode* current = open.back();
			open.pop_back();

			// Add occupants if they are in the region
			for(auto &it : current->occupants)
			{
				QuadTreeOccupant* occupant = it;

				if(region.intersects(occupant->aabb))
				{
					// Intersects, add to list
					result.push_back(occupant);
				}
			}

			// Add children to open list if they intersect the region
			if(current->hasChildren)
			{
				for(int x = 0; x < 2; x++)
					for(int y = 0; y < 2; y++)
					{
						if(region.intersects((*current->children)[x][y].region))
							open.push_back(&(*current->children)[x][y]);
					}
			}
		}
	}

	void QuadTree::debugRender()
	{
		// Render outside root AABB's
		glColor3f(0.5f, 0.2f, 0.1f);

		for(auto &it : outsideRoot)
			it->aabb.debugRender();

		// Now draw the tree
		std::list<QuadTreeNode*> open;

		open.push_back(root.get());

		while(!open.empty())
		{
			// Depth-first (results in less memory usage), remove objects from open list
			QuadTreeNode* current = open.back();
			open.pop_back();

			// Render node region AABB
			glColor3f(0.4f, 0.9f, 0.7f);

			current->region.debugRender();

			glColor3f(0.5f, 0.2f, 0.2f);

			// Render occupants
			for(auto &it : current->occupants)
			{
				QuadTreeOccupant* occupant = it;

				occupant->aabb.debugRender();
			}

			// Add children to open list if they are visible
			if(current->hasChildren)
			{
				for(int x = 0; x < 2; x++)
					for(int y = 0; y < 2; y++)
						open.push_back(&(*current->children)[x][y]);
			}
		}
	}
}
