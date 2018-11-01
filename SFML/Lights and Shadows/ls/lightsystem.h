#pragma once
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>

#include "staticquadtree.h"
#include "light.h"
#include "emissivelight.h"
#include "convexHull.h"
#include "shadowfin.h"

namespace ls
{
	class LightSystem
	{
	private:
		sf::RenderWindow* window;

		std::unordered_set<Light*> lights;
		std::unordered_set<EmissiveLight*> emissiveLights;
		std::unordered_set<ConvexHull*> convexHulls;

		std::vector<Light*> lightsToPreBuild;

		qdt::StaticQuadTree lightTree;
		qdt::StaticQuadTree hullTree;
		qdt::StaticQuadTree emissiveTree;

		sf::RenderTexture compositionTexture;
		sf::RenderTexture lightTempTexture;
		sf::RenderTexture bloomTexture;

		sf::Shader lightAttenuationShader;
		sf::Texture softShadowTexture;

		int prebuildTimer;

		void maskShadow(Light* light, ConvexHull* convexHull, bool minPoly, float depth);

		// Returns number of fins added
		int addExtraFins(const ConvexHull &hull, std::vector<ShadowFin> &fins, const Light &light, int boundryIndex, bool wrapCW, Vec2f &mainUmbraRoot, Vec2f &mainUmbraVec);

		void cameraSetup();
		void setUp(const AABB &region);

		// Switching between render textures
		void switchLightTemp();
		void switchComposition();
		void switchBloom();
		void switchWindow();
		void switchWindowProjection();

		enum CurrentRenderTexture
		{
			cur_lightTemp, cur_shadow, cur_main, cur_bloom, cur_window, cur_lightStatic
		} currentRenderTexture;

		void clearLightTexture(sf::RenderTexture &renTex);

	public:
		AABB viewAABB;
		sf::Color ambientColor;
		bool checkForHullIntersect;
		bool useBloom;
		unsigned int maxFins;

		LightSystem();
		LightSystem(const AABB &region, sf::RenderWindow* pRenderWindow, const std::string &finImagePath, const std::string &lightAttenuationShaderPath);
		~LightSystem();

		void create(const AABB &region, sf::RenderWindow* pRenderWindow, const std::string &finImagePath, const std::string &lightAttenuationShaderPath);

		void setView(const sf::View &view);

		// All objects are controller through pointer, but these functions return indices that allow easy removal
		void addLight(Light* newLight);
		void addConvexHull(ConvexHull* newConvexHull);
		void addEmissiveLight(EmissiveLight* newEmissiveLight);

		void removeLight(Light* pLight);
		void removeConvexHull(ConvexHull* pHull);
		void removeEmissiveLight(EmissiveLight* pEmissiveLight);

		
		void buildLight(Light* pLight);	// Pre-builds the light

		void clearLights();
		void clearConvexHulls();
		void clearEmissiveLights();

		void renderLights();	// Renders lights to the light texture
		void renderLightTexture();
		void debugRender();
	};
}