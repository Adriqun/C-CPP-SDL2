#pragma once
#include "aabb.h"
#include "point2i.h"
#include "quadtreeoccupant.h"

#include <vector>
#include <unordered_set>
#include <memory>
#include <list>

namespace qdt
{
	class QuadTreeNode
	{
		class QuadTreeNode* parent;
		class QuadTree* tree;

		bool hasChildren;
		std::vector<std::vector<QuadTreeNode>>* children;	// Cannot use a unique_ptr, since the vector requires copy ctor/assignment ops
		

		std::unordered_set<class QuadTreeOccupant*> occupants;

		AABB region;
		int level;
		int numOccupantsBelow;

		inline QuadTreeNode* getChild(const Point2i position);

		void getPossibleOccupantPosition(QuadTreeOccupant* pOc, Point2i &point);
		void getOccupants(std::unordered_set<QuadTreeOccupant*> &occupants);

		void addToThisLevel(QuadTreeOccupant* occupant);
		bool addToChildren(QuadTreeOccupant* occupant);	// Returns true if occupant was added to children

		void partition();
		void destroyChildren();
		void merge();

		void update(QuadTreeOccupant* occupant);
		void remove(QuadTreeOccupant* occupant);

	public:
		static int minNumOccupants;
		static int maxNumOccupants;
		static int maxNumLevels;
		static float oversizeMultiplier;

		QuadTreeNode();
		QuadTreeNode(const AABB &region, int level, QuadTreeNode* parent = nullptr, QuadTree* tree = nullptr);
		~QuadTreeNode();

		void create(const AABB &region, int level, QuadTreeNode* parent = nullptr, QuadTree* tree = nullptr); // For use after using default constructor
		void add(QuadTreeOccupant* occupant);

		QuadTree* getTree();
		const AABB &getRegion();
		void getAllOccupantsBelow(std::vector<QuadTreeOccupant*> &occupants);

		friend class QuadTreeOccupant;
		friend class QuadTree;
	};
}