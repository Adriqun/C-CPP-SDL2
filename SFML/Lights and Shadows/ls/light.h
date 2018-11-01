#pragma once
#include "constructs.h"
#include "quadtree.h"

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ls
{
	class Light : public qdt::QuadTreeOccupant
	{
		bool updateRequired;
		bool alwaysUpdate;
		sf::RenderWindow* window;
		sf::RenderTexture* staticTexture;
		void switchStaticTexture(); // Set up viewport information for the render texture

	protected:
		class LightSystem* ls;

		// Set to false in base classes in order to avoid shader attenuation
		bool shaderAttenuation;

	public:
		Vec2f center;
		float intensity;
		float radius;
		float size;

		// If using light autenuation shader
		float bleed;
		float linearizeFactor;

		Color3f color;

		Light();
		~Light();

		void setRadius(float newRadius);
		void incRadius(float increment);
		const float &getRadius() const;

		void setCenter(Vec2f newCenter);
		void incCenter(Vec2f increment);
		const Vec2f &getCenter() const;

		virtual void renderLightSolidPortion() = 0;
		virtual void renderLightSoftPortion() = 0;
		virtual void calculateAABB();
		AABB* getAABB();

		const bool &isAlwaysUpdate() const;
		void setAlwaysUpdate(bool always);

		friend class LightSystem;
	};
}