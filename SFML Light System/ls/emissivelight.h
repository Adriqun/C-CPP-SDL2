#pragma once
#include "quadtree.h"
#include "color3f.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ls
{
	class EmissiveLight : public qdt::QuadTreeOccupant
	{
	private:
		sf::Texture* texture;
		float angleDegs;
		Vec2f halfRenderDims;

	public:
		float intensity;
		Color3f color;

		EmissiveLight();

		void setTexture(sf::Texture* newTexture);
		void render();

		void setCenter(const Vec2f &newCenter);
		void setDims(const Vec2f &newScale);
		void incCenter(const Vec2f &increment);
		void setRotation(float angle);
		void incRotation(float increment);

		Vec2f getDims();
		const Vec2f &getCenter() const;
		const float &getAngle() const;
	};
}