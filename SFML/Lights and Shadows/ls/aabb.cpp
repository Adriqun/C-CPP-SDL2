#include "aabb.h"
#include <SFML/OpenGL.hpp>
#include <cmath>

AABB::AABB()
{
	center = Vec2f(0.5f, 0.5f);
	halfDims = Vec2f(0.5f, 0.5f);
	lowerBound = Vec2f(0.0f, 0.0f);
	upperBound = Vec2f(1.0f, 1.0f);
}

AABB::AABB(const Vec2f &lowerBound, const Vec2f &upperBound)
{
	this->lowerBound = lowerBound;
	this->upperBound = upperBound;
	calculateHalfDims();
	calculateCenter();
}

void AABB::calculateHalfDims()
{
	halfDims = (upperBound - lowerBound) / 2.0f;
}

void AABB::calculateCenter()
{
	center = lowerBound + halfDims;
}

void AABB::calculateBounds()
{
	lowerBound = center - halfDims;
	upperBound = center + halfDims;
}

const Vec2f &AABB::getCenter() const
{
	return center;
}

Vec2f AABB::getDims() const
{
	return upperBound - lowerBound;
}

const Vec2f &AABB::getHalfDims() const
{
	return halfDims;
}

const Vec2f &AABB::getLowerBound() const
{
	return lowerBound;
}

const Vec2f &AABB::getUpperBound() const
{
	return upperBound;
}

AABB AABB::getRotatedAABB(float angle) const
{
	// Get new dimensions
	float cosOfAngle = cosf(angle);
	float sinOfAngle = sinf(angle);

	Vec2f newHalfDims(halfDims.y * sinOfAngle + halfDims.x * cosOfAngle, halfDims.x * sinOfAngle + halfDims.y * cosOfAngle);

	return AABB(center - newHalfDims, center + newHalfDims);
}

void AABB::setCenter(const Vec2f &newCenter)
{
	center = newCenter;
	calculateBounds();
}

void AABB::incCenter(const Vec2f &increment)
{
	center += increment;
	calculateBounds();
}

void AABB::setDims(const Vec2f &newDims)
{
	setHalfDims(newDims / 2.0f);
}

void AABB::setHalfDims(const Vec2f &newDims)
{
	halfDims = newDims;
	calculateBounds();
}

void AABB::setRotatedAABB(float angle)
{
	float cosOfAngle = std::cos(angle);
	float sinOfAngle = std::sin(angle);

	halfDims.x = halfDims.y * sinOfAngle + halfDims.x * cosOfAngle;
	halfDims.y = halfDims.x * sinOfAngle + halfDims.y * cosOfAngle;
}

bool AABB::intersects(const AABB &other) const
{
	if(upperBound.x < other.lowerBound.x)
		return false;

	if(upperBound.y < other.lowerBound.y)
		return false;

	if(lowerBound.x > other.upperBound.x)
		return false;

	if(lowerBound.y > other.upperBound.y)
		return false;

	return true;
}

bool AABB::contains(const AABB &other) const
{
	if(other.lowerBound.x >= lowerBound.x &&
		other.upperBound.x <= upperBound.x &&
		other.lowerBound.y >= lowerBound.y &&
		other.upperBound.y <= upperBound.y)
		return true;

	return false;
}

void AABB::debugRender()
{
	// Render the AABB with lines
	glBegin(GL_LINES);
	
	// Bottom
	glVertex2f(lowerBound.x, lowerBound.y);
	glVertex2f(upperBound.x, lowerBound.y);

	// Right
	glVertex2f(upperBound.x, lowerBound.y);
	glVertex2f(upperBound.x, upperBound.y);

	// Top
	glVertex2f(upperBound.x, upperBound.y);
	glVertex2f(lowerBound.x, upperBound.y);

	// Left
	glVertex2f(lowerBound.x, upperBound.y);
	glVertex2f(lowerBound.x, lowerBound.y);

	glEnd();
}
