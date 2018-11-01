#pragma once
#include "vec2f.h"

class AABB
{
	Vec2f center;
	Vec2f halfDims;

public:
	Vec2f lowerBound;
	Vec2f upperBound;

	AABB();
	AABB(const Vec2f &lowerBound, const Vec2f &upperBound);

	void calculateHalfDims();
	void calculateCenter();
	void calculateBounds();

	// Accessors
	const Vec2f &getCenter() const;
	Vec2f getDims() const;
	const Vec2f &getHalfDims() const;
	const Vec2f &getLowerBound() const;
	const Vec2f &getUpperBound() const;
	AABB getRotatedAABB(float angle) const;

	// Modifiers
	void setLowerBound(const Vec2f &newLowerBound);
	void setUpperBound(const Vec2f &newUpperBound);
	void setCenter(const Vec2f &newCenter);
	void incCenter(const Vec2f &increment);
	void setDims(const Vec2f &newDims);
	void setHalfDims(const Vec2f &newDims);
	void setRotatedAABB(float angle);

	// Utility
	bool intersects(const AABB &other) const;
	bool contains(const AABB &other) const;

	// Render the AABB for debugging purposes
	void debugRender();
};