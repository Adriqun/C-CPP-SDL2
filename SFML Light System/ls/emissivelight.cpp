/*
Let There Be Light
Copyright (C) 2012 Eric Laukien

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
Update by Adrian Michalek 2018.10.18
- Some functions were updated and shorten.
- Some code were deleted due to regressions and depracations.
- Names of variables and functions were changed.
- Functionality stays the same.
*/

#pragma once
#include "emissivelight.h"
#include "utils.h"
#include <cmath>

ls::EmissiveLight::EmissiveLight()
{
	angleDegs = 0.0f;
	color = Color3f(1.0f, 1.0f, 1.0f);
	intensity = 1.0f;
}

void ls::EmissiveLight::setTexture(sf::Texture* newTexture)
{
	texture = newTexture;

	// Update aabb and the render dims
	sf::Vector2u textureSize(texture->getSize());
	halfRenderDims.x = static_cast<float>(textureSize.x) / 2.0f;
	halfRenderDims.y = static_cast<float>(textureSize.y) / 2.0f;

	aabb.setHalfDims(halfRenderDims);
	aabb.calculateHalfDims();
	aabb.calculateCenter();
	update();
}

void ls::EmissiveLight::render()
{
	glPushMatrix();

	const Vec2f &center = aabb.getCenter();

	sf::Texture::bind(texture);

	glTranslatef(center.x, center.y, 0.0f);
	glRotatef(angleDegs, 0.0f, 0.0f, 1.0f);

	// Clamp the intensity
	float renderIntensity = intensity;

	if(renderIntensity > 1.0f)
		renderIntensity = 1.0f;

	glColor4f(color.r, color.g, color.b, renderIntensity);

	// Have to render upside-down because SFML loads the Textures upside-down
	glBegin(GL_QUADS);
		glTexCoord2i(0, 0); glVertex2f(-halfRenderDims.x, -halfRenderDims.y);
		glTexCoord2i(1, 0); glVertex2f(halfRenderDims.x, -halfRenderDims.y);
		glTexCoord2i(1, 1); glVertex2f(halfRenderDims.x, halfRenderDims.y);
		glTexCoord2i(0, 1); glVertex2f(-halfRenderDims.x, halfRenderDims.y);
	glEnd();

	// Reset color
	glColor3f(1.0f,	1.0f, 1.0f);

	glPopMatrix();
}

void ls::EmissiveLight::setCenter(const Vec2f &newCenter)
{
	aabb.setCenter(newCenter);
	update();
}

void ls::EmissiveLight::incCenter(const Vec2f &increment)
{
	aabb.incCenter(increment);
	update();
}

void ls::EmissiveLight::setDims(const Vec2f &newDims)
{
	halfRenderDims = newDims / 2.0f;

	// Set AABB
	aabb.setHalfDims(halfRenderDims);
	
	// Re-rotate AABB if it is rotated
	if(angleDegs != 0.0f)
		setRotation(angleDegs);

	update();
}

void ls::EmissiveLight::setRotation(float angle)
{
	// Update the render angle (convert to degrees)
	angleDegs = angle;

	// Get original AABB
	aabb.setHalfDims(halfRenderDims);

	aabb.calculateHalfDims();
	aabb.calculateCenter();

	// If angle is the normal angle, exit
	if(angleDegs == 0.0f)
		return;

	// Get angle in radians
	float angleRads = angleDegs * (static_cast<float>(PI) / 180.0f);

	// Rotate the aabb
	aabb.setRotatedAABB(angleRads);

	update();
}

void ls::EmissiveLight::incRotation(float increment)
{
	// Increment render angle
	angleDegs += increment;

	// Get angle increment in radians
	float incrementRads = increment * (static_cast<float>(PI) / 180.0f);

	// Rotate the aabb without setting to original aabb, so rotation is relative
	aabb.setRotatedAABB(incrementRads);
}

Vec2f ls::EmissiveLight::getDims()
{
	return aabb.getDims();
}

const Vec2f &ls::EmissiveLight::getCenter() const
{
	return aabb.getCenter();
}

const float &ls::EmissiveLight::getAngle() const
{
	return angleDegs;
}
