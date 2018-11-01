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
#include "lightsystem.h"
#include "utils.h"
#include <cstdlib>
#include <cassert>

namespace ls
{
	LightSystem::LightSystem()
		: ambientColor(55, 55, 55), checkForHullIntersect(true),
		prebuildTimer(0), useBloom(true), maxFins(1)
	{
	}

	LightSystem::LightSystem(const AABB &region, sf::RenderWindow* pRenderWindow, const std::string &finImagePath, const std::string &lightAttenuationShaderPath)
		: ambientColor(55, 55, 55), checkForHullIntersect(true),
		prebuildTimer(0), window(pRenderWindow), useBloom(true), maxFins(1)
	{
		// Load the soft shadows texture
		if(!softShadowTexture.loadFromFile(finImagePath))
			std::abort(); // Could not find the texture, abort

		if(!lightAttenuationShader.loadFromFile(lightAttenuationShaderPath, sf::Shader::Fragment))
			std::abort();

		setUp(region);
	}

	LightSystem::~LightSystem()
	{
		// Destroy resources
		clearLights();
		clearConvexHulls();
		clearEmissiveLights();
	}

	void LightSystem::create(const AABB &region, sf::RenderWindow* pRenderWindow, const std::string &finImagePath, const std::string &lightAttenuationShaderPath)
	{
		window = pRenderWindow;

		// Load the soft shadows texture
		if(!softShadowTexture.loadFromFile(finImagePath))
			std::abort(); // Could not find the texture, abort

		if(!lightAttenuationShader.loadFromFile(lightAttenuationShaderPath, sf::Shader::Fragment))
			std::abort();

		setUp(region);
	}

	void LightSystem::setView(const sf::View &view)
	{
		sf::Vector2f viewSize(view.getSize());
		viewAABB.setDims(Vec2f(viewSize.x, viewSize.y));
		sf::Vector2f viewCenter(view.getCenter());

		// Flipped
		viewAABB.setCenter(Vec2f(viewCenter.x, viewSize.y - viewCenter.y));
	}

	void LightSystem::cameraSetup()
	{
		glLoadIdentity();
		glTranslatef(-viewAABB.lowerBound.x, -viewAABB.lowerBound.y, 0.0f);
	}

	void LightSystem::maskShadow(Light* light, ConvexHull* convexHull, bool minPoly, float depth)
	{
		// ----------------------------- Determine the Shadow Boundaries -----------------------------

		Vec2f lCenter(light->center);
		float lRadius = light->radius;

		Vec2f hCenter(convexHull->getWorldCenter());

		const int numVertices = convexHull->vertices.size();

		std::vector<bool> backFacing(numVertices);

		for(int i = 0; i < numVertices; i++)
		{
			Vec2f firstVertex(convexHull->getWorldVertex(i));
			int secondIndex = (i + 1) % numVertices;
			Vec2f secondVertex(convexHull->getWorldVertex(secondIndex));
			Vec2f middle((firstVertex + secondVertex) / 2.0f);

			// Use normal to take light width into account, this eliminates popping
			Vec2f lightNormal(-(lCenter.y - middle.y), lCenter.x - middle.x);

			Vec2f centerToBoundry(middle - hCenter);

			if(centerToBoundry.dot(lightNormal) < 0)
				lightNormal *= -1;

			lightNormal = lightNormal.normalize() * light->size;

			Vec2f L((lCenter - lightNormal) - middle);
                
			if (convexHull->normals[i].dot(L) > 0)
				backFacing[i] = false;
			else
				backFacing[i] = true;
		}

		int firstBoundryIndex = 0;
		int secondBoundryIndex = 0;

		for(int currentEdge = 0; currentEdge < numVertices; currentEdge++)
		{
			int nextEdge = (currentEdge + 1) % numVertices;

			if (backFacing[currentEdge] && !backFacing[nextEdge])
				firstBoundryIndex = nextEdge;

			if (!backFacing[currentEdge] && backFacing[nextEdge])
				secondBoundryIndex = nextEdge;
		}

		// -------------------------------- Shadow Fins --------------------------------

		Vec2f firstBoundryPoint(convexHull->getWorldVertex(firstBoundryIndex));

		Vec2f lightNormal(-(lCenter.y - firstBoundryPoint.y), lCenter.x - firstBoundryPoint.x);

		Vec2f centerToBoundry(firstBoundryPoint - hCenter);

		if(centerToBoundry.dot(lightNormal) < 0)
			lightNormal *= -1;

		lightNormal = lightNormal.normalize() * light->size;

		ShadowFin firstFin;

		firstFin.rootPos = firstBoundryPoint;
		firstFin.umbra = firstBoundryPoint - (lCenter + lightNormal);
		firstFin.umbra = firstFin.umbra.normalize() * lRadius;

		firstFin.penumbra = firstBoundryPoint - (lCenter - lightNormal);
		firstFin.penumbra = firstFin.penumbra.normalize() * lRadius;

		ShadowFin secondFin;

		Vec2f secondBoundryPoint = convexHull->getWorldVertex(secondBoundryIndex);

		lightNormal.x = -(lCenter.y - secondBoundryPoint.y);
		lightNormal.y = lCenter.x - secondBoundryPoint.x;

		centerToBoundry = secondBoundryPoint - hCenter;

		if(centerToBoundry.dot(lightNormal) < 0)
			lightNormal *= -1;

		lightNormal = lightNormal.normalize() * light->size;

		secondFin.rootPos = secondBoundryPoint;
		secondFin.umbra = secondBoundryPoint - (lCenter + lightNormal);
		secondFin.umbra = secondFin.umbra.normalize() * lRadius;
	
		secondFin.penumbra = secondBoundryPoint - (lCenter - lightNormal);
		secondFin.penumbra = secondFin.penumbra.normalize() * lRadius;

		std::vector<ShadowFin> finsToRender_firstBoundary;
		std::vector<ShadowFin> finsToRender_secondBoundary;

		// Store generated fins to render later
		// First two, will always be there
		finsToRender_firstBoundary.push_back(firstFin);
		finsToRender_secondBoundary.push_back(secondFin);

		// Need to get address of fin in array instead of firstFin/secondFin since they are copies, and we want it to be modified directly
		// Can avoid by not creating firstFin and secondFin and instead using finsToRender[0] and finsToRender[1]
		// Also, move the boundary points for rendering depending on the number of hulls added
		Vec2f mainUmbraRoot1;
		Vec2f mainUmbraVec1;

		firstBoundryIndex = wrap(firstBoundryIndex + addExtraFins(*convexHull, finsToRender_firstBoundary, *light, firstBoundryIndex, false, mainUmbraRoot1, mainUmbraVec1), numVertices);

		Vec2f mainUmbraRoot2;
		Vec2f mainUmbraVec2;

		secondBoundryIndex = wrap(secondBoundryIndex - addExtraFins(*convexHull, finsToRender_secondBoundary, *light, secondBoundryIndex, true, mainUmbraRoot2, mainUmbraVec2), numVertices);

		// ----------------------------- Drawing the umbra -----------------------------

		glDisable(GL_TEXTURE_2D);

		glBlendFunc(GL_ZERO, GL_SRC_ALPHA);

		glColor4f(0.0f, 0.0f, 0.0f, 1.0f - convexHull->transparency);

		if(!convexHull->renderLightOverHull)
		{
			Vec2f throughCenter((hCenter - lCenter).normalize() * lRadius);

			// 3 rays all the time, less polygons
			glBegin(GL_TRIANGLE_STRIP);

			glVertex3f(mainUmbraRoot1.x, mainUmbraRoot1.y, depth);
			glVertex3f(mainUmbraRoot1.x + mainUmbraVec1.x, mainUmbraRoot1.y + mainUmbraVec1.y, depth);
			glVertex3f(hCenter.x, hCenter.y, depth);
			glVertex3f(hCenter.x + throughCenter.x, hCenter.y + throughCenter.y, depth);
			glVertex3f(mainUmbraRoot2.x, mainUmbraRoot2.y, depth);
			glVertex3f(mainUmbraRoot2.x + mainUmbraVec2.x, mainUmbraRoot2.y + mainUmbraVec2.y, depth);

			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLE_STRIP);

			// Umbra and penumbra sides done separately, since they do not follow light rays
			glVertex3f(mainUmbraRoot1.x, mainUmbraRoot1.y, depth);
			glVertex3f(mainUmbraRoot1.x + mainUmbraVec1.x, mainUmbraRoot1.y + mainUmbraVec1.y, depth);

			int endV; 

			if(firstBoundryIndex < secondBoundryIndex)
				endV = secondBoundryIndex - 1;
			else
				endV = secondBoundryIndex + numVertices - 1;

			// Mask off around the hull, requires more polygons
			for(int v = firstBoundryIndex + 1; v <= endV; v++)
			{
				// Get actual vertex
				int vi = v % numVertices;

				Vec2f startVert(convexHull->getWorldVertex(vi));
				Vec2f endVert((startVert - light->center).normalize() * light->radius + startVert);

				// 2 points for ray in strip
				glVertex3f(startVert.x, startVert.y, depth);
				glVertex3f(endVert.x, endVert.y, depth);
			}

			glVertex3f(mainUmbraRoot2.x, mainUmbraRoot2.y, depth);
			glVertex3f(mainUmbraRoot2.x + mainUmbraVec2.x, mainUmbraRoot2.y + mainUmbraVec2.y, depth);

			glEnd();
		}

		// Render shadow fins
		glEnable(GL_TEXTURE_2D);

		sf::Texture::bind(&softShadowTexture);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		for(unsigned int f = 0, numFins = finsToRender_firstBoundary.size(); f < numFins; f++)
			finsToRender_firstBoundary[f].render(convexHull->transparency);

		for(unsigned int f = 0, numFins = finsToRender_secondBoundary.size(); f < numFins; f++)
			finsToRender_secondBoundary[f].render(convexHull->transparency);
	}

	int LightSystem::addExtraFins(const ConvexHull &hull, std::vector<ShadowFin> &fins, const Light &light, int boundryIndex, bool wrapCW, Vec2f &mainUmbraRoot, Vec2f &mainUmbraVec)
	{
		ShadowFin* pFin = &fins.back();

		Vec2f hCenter(hull.getWorldCenter());

		int secondEdgeIndex;
		int numVertices = static_cast<signed>(hull.vertices.size());

		mainUmbraRoot = fins.back().rootPos;
		mainUmbraVec = fins.back().umbra;

		unsigned int i;

		for(i = 0; i < maxFins; i++)
		{	
			if(wrapCW)
				secondEdgeIndex = wrap(boundryIndex - 1, numVertices);
			else
				secondEdgeIndex = wrap(boundryIndex + 1, numVertices);

			Vec2f edgeVec((hull.vertices[secondEdgeIndex] - hull.vertices[boundryIndex]).normalize());

			Vec2f penNorm(pFin->penumbra.normalize());

			float angle1 = acosf(penNorm.dot(edgeVec));
			float angle2 = acosf(penNorm.dot(pFin->umbra.normalize()));

			if(angle1 >= angle2)
				break; // No intersection, break

			// Change existing fin to attatch to side of hull
			pFin->umbra = edgeVec * light.radius;

			// Calculate a lower fin instensity based on ratio of angles (0 if angles are same, so disappears then)
			pFin->umbraBrightness = 1.0f - angle1 / angle2;

			// Add the extra fin
			Vec2f secondBoundryPoint(hull.getWorldVertex(secondEdgeIndex));

			Vec2f lightNormal(-(light.center.y - secondBoundryPoint.y), light.center.x - secondBoundryPoint.x);

			Vec2f centerToBoundry(secondBoundryPoint - hCenter);

			if(centerToBoundry.dot(lightNormal) < 0)
				lightNormal *= -1;

			lightNormal = lightNormal.normalize() * light.size;

			ShadowFin newFin;

			mainUmbraRoot = newFin.rootPos = secondBoundryPoint;
			newFin.umbra = secondBoundryPoint - (light.center + lightNormal);
			mainUmbraVec = newFin.umbra = newFin.umbra.normalize() * light.radius;
			newFin.penumbra = pFin->umbra;

			newFin.penumbraBrightness = pFin->umbraBrightness;

			fins.push_back(newFin);

			pFin = &fins.back();

			boundryIndex = secondEdgeIndex;
		}

		return i;
	}

	void LightSystem::setUp(const AABB &region)
	{
		// Create the quad trees
		lightTree.create(region);
		hullTree.create(region);
		emissiveTree.create(region);

		// Base RT size off of window resolution
		sf::Vector2u viewSizeui(window->getSize());

		sf::ContextSettings cs = sf::ContextSettings();
		cs.depthBits = 0;

		compositionTexture.create(viewSizeui.x, viewSizeui.y, cs);
		compositionTexture.setSmooth(true);

		compositionTexture.setActive();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);

		

		bloomTexture.create(viewSizeui.x, viewSizeui.y, cs);
		bloomTexture.setSmooth(true);

		bloomTexture.setActive();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		
		lightTempTexture.create(viewSizeui.x, viewSizeui.y, cs);
		lightTempTexture.setSmooth(true);

		lightTempTexture.setActive();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);

		window->setActive();
	}

	void LightSystem::addLight(Light* newLight)
	{
		newLight->window = window;
		newLight->ls = this;
		lights.insert(newLight);
		lightTree.add(newLight);
	}

	void LightSystem::addConvexHull(ConvexHull* newConvexHull)
	{
		convexHulls.insert(newConvexHull);
		hullTree.add(newConvexHull);
	}

	void LightSystem::addEmissiveLight(EmissiveLight* newEmissiveLight)
	{
		emissiveLights.insert(newEmissiveLight);
		emissiveTree.add(newEmissiveLight);
	}

	void LightSystem::removeLight(Light* pLight)
	{
		std::unordered_set<Light*>::iterator it = lights.find(pLight);

		assert(it != lights.end());

		(*it)->remove();

		lights.erase(it);

		delete pLight;
	}

	void LightSystem::removeConvexHull(ConvexHull* pHull)
	{
		std::unordered_set<ConvexHull*>::iterator it = convexHulls.find(pHull);

		assert(it != convexHulls.end());

		(*it)->remove();

		convexHulls.erase(it);

		delete pHull;
	}

	void LightSystem::removeEmissiveLight(EmissiveLight* pEmissiveLight)
	{
		std::unordered_set<EmissiveLight*>::iterator it = emissiveLights.find(pEmissiveLight);

		assert(it != emissiveLights.end());

		(*it)->remove();

		emissiveLights.erase(it);

		delete pEmissiveLight;
	}

	void LightSystem::clearLights()
	{
		// Delete contents
		for(std::unordered_set<Light*>::iterator it = lights.begin(); it != lights.end(); it++)
			delete *it;

		lights.clear();

		if(lightTree.isCreated())
		{
			lightTree.clear();
			lightTree.create(AABB(Vec2f(-50.0f, -50.0f), Vec2f(-50.0f, -50.0f)));
		}
	}

	void LightSystem::clearConvexHulls()
	{
		// Delete contents
		for(std::unordered_set<ConvexHull*>::iterator it = convexHulls.begin(); it != convexHulls.end(); it++)
			delete *it;

		convexHulls.clear();

		if(!hullTree.isCreated())
		{
			hullTree.clear();
			hullTree.create(AABB(Vec2f(-50.0f, -50.0f), Vec2f(-50.0f, -50.0f)));
		}
	}

	void LightSystem::clearEmissiveLights()
	{
		// Delete contents
		for(std::unordered_set<EmissiveLight*>::iterator it = emissiveLights.begin(); it != emissiveLights.end(); it++)
			delete *it;

		emissiveLights.clear();

		if(emissiveTree.isCreated())
		{
			emissiveTree.clear();
			emissiveTree.create(AABB(Vec2f(-50.0f, -50.0f), Vec2f(-50.0f, -50.0f)));
		}
	}

	void LightSystem::switchLightTemp()
	{
		if(currentRenderTexture != cur_lightTemp)
		{
			lightTempTexture.setActive();

			//if(currentRenderTexture == cur_lightStatic)
				switchWindowProjection();

			currentRenderTexture = cur_lightTemp;
		}
	}

	void LightSystem::switchComposition()
	{
		if(currentRenderTexture != cur_main)
		{
			compositionTexture.setActive();

			if(currentRenderTexture == cur_lightStatic)
				switchWindowProjection();

			currentRenderTexture = cur_main;
		}
	}

	void LightSystem::switchBloom()
	{
		if(currentRenderTexture != cur_bloom)
		{
			bloomTexture.setActive();

			if(currentRenderTexture == cur_lightStatic)
				switchWindowProjection();

			currentRenderTexture = cur_bloom;
		}
	}

	void LightSystem::switchWindow()
	{
		window->resetGLStates();
	}

	void LightSystem::switchWindowProjection()
	{
		Vec2f viewSize(viewAABB.getDims());
		sf::Vector2u viewSizeui(static_cast<unsigned int>(viewSize.x), static_cast<unsigned int>(viewSize.y));

		glViewport(0, 0, viewSizeui.x, viewSizeui.y);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Upside-down, because SFML is pro like that
		glOrtho(0, viewSize.x, 0, viewSize.y, -100.0f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
	}

	void LightSystem::clearLightTexture(sf::RenderTexture &renTex)
	{	
		glLoadIdentity();
				
		renTex.clear(sf::Color::Transparent);

		// Clear with quad, since glClear is not working for some reason... if results in very ugly artifacts. MUST clear with full color, with alpha!
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);

		sf::Vector2u size(renTex.getSize());
		float width = static_cast<float>(size.x);
		float height = static_cast<float>(size.y);

		glBlendFunc(GL_ONE, GL_ZERO);

		glBegin(GL_QUADS);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(width, 0.0f);
			glVertex2f(width, height);
			glVertex2f(0.0f, height);
		glEnd();
	}

	void LightSystem::renderLights()
	{
		// So will switch to main render textures from SFML projection
		currentRenderTexture = cur_lightStatic;

		Vec2f viewCenter(viewAABB.getCenter());
		Vec2f viewSize(viewAABB.getDims());

		glDisable(GL_TEXTURE_2D);

		if(useBloom)
		{
			// Clear the bloom texture
			switchBloom();
			glLoadIdentity();

			bloomTexture.clear(sf::Color::Transparent);

			glColor4f(0.0f, 0.0f, 0.0f, 0.0f);

			glBlendFunc(GL_ONE, GL_ZERO);

			// Clear with quad, since glClear is not working for some reason... if results in very ugly artifacts
			glBegin(GL_QUADS);
				glVertex2f(0.0f, 0.0f);
				glVertex2f(viewSize.x, 0.0f);
				glVertex2f(viewSize.x, viewSize.y);
				glVertex2f(0.0f, viewSize.y);
			glEnd();

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}

		switchComposition();
		glLoadIdentity();

		compositionTexture.clear(ambientColor);

		glColor4b(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);

		glBlendFunc(GL_ONE, GL_ZERO);

		// Clear with quad, since glClear is not working for some reason... if results in very ugly artifacts
		glBegin(GL_QUADS);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(viewSize.x, 0.0f);
			glVertex2f(viewSize.x, viewSize.y);
			glVertex2f(0.0f, viewSize.y);
		glEnd();

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_2D);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Get visible lights
		std::vector<qdt::QuadTreeOccupant*> visibleLights;
		lightTree.queryRegion(viewAABB, visibleLights);

		// Add lights from pre build list if there are any
		if(!lightsToPreBuild.empty())
		{
			if(prebuildTimer < 2)
			{
				prebuildTimer++;

				const unsigned int numLightsToPreBuild = lightsToPreBuild.size();

				for(unsigned int i = 0; i < numLightsToPreBuild; i++)
				{
					lightsToPreBuild[i]->updateRequired = true;
					visibleLights.push_back(lightsToPreBuild[i]);
				}
			}
			else
				lightsToPreBuild.clear();
		}

		const unsigned int numVisibleLights = visibleLights.size();

		for(unsigned int l = 0; l < numVisibleLights; l++)
		{
			Light* pLight = static_cast<Light*>(visibleLights[l]);

			// Skip invisible lights
			if(pLight->intensity == 0.0f)
				continue;

			bool updateRequired = false;

			if(pLight->isAlwaysUpdate())
				updateRequired = true;
			else if(pLight->updateRequired)
				updateRequired = true;

			// Get hulls that the light affects
			std::vector<qdt::QuadTreeOccupant*> regionHulls;
			hullTree.queryRegion(*pLight->getAABB(), regionHulls);

			const unsigned int numHulls = regionHulls.size();

			if(!updateRequired)
			{
				// See of any of the hulls need updating
				for(unsigned int h = 0; h < numHulls; h++)
				{
					ConvexHull* pHull = static_cast<ConvexHull*>(regionHulls[h]);

					if(pHull->updateRequired)
					{
						pHull->updateRequired = false;
						updateRequired = true;
						break;
					}
				}
			}

			if(updateRequired)
			{
				Vec2f staticTextureOffset;

				// Activate the intermediate render Texture
				if(pLight->isAlwaysUpdate())
				{
					switchLightTemp();

					clearLightTexture(lightTempTexture);

					cameraSetup();

					// Reset color
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					pLight->switchStaticTexture();
					currentRenderTexture = cur_lightStatic;

					clearLightTexture(*pLight->staticTexture);

					// Reset color
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

					staticTextureOffset = pLight->aabb.getDims() / 2.0f;

					glTranslatef(-pLight->aabb.lowerBound.x, -pLight->aabb.lowerBound.y, 0.0f);
				}

				if(pLight->shaderAttenuation)
				{
					sf::Shader::bind(&lightAttenuationShader);

					if(pLight->isAlwaysUpdate())
						lightAttenuationShader.setUniform("lightPos", sf::Glsl::Vec2(pLight->center.x - viewAABB.lowerBound.x, pLight->center.y - viewAABB.lowerBound.y));
					else
						lightAttenuationShader.setUniform("lightPos", sf::Glsl::Vec2(pLight->center.x - pLight->aabb.lowerBound.x, pLight->center.y - pLight->aabb.lowerBound.y));

					lightAttenuationShader.setUniform("lightColor", sf::Glsl::Vec3(pLight->color.r, pLight->color.g, pLight->color.b));
					lightAttenuationShader.setUniform("radius", pLight->radius);
					lightAttenuationShader.setUniform("bleed", pLight->bleed);
					lightAttenuationShader.setUniform("linearizeFactor", pLight->linearizeFactor);

					// Render the current light
					pLight->renderLightSolidPortion();

					sf::Shader::bind(NULL);
				}
				else
					// Render the current light
					pLight->renderLightSolidPortion();

				// Mask off lights
				if(checkForHullIntersect)
					for(unsigned int h = 0; h < numHulls; h++)
					{
						ConvexHull* pHull = static_cast<ConvexHull*>(regionHulls[h]);

						Vec2f hullToLight(pLight->center - pHull->getWorldCenter());
						hullToLight = hullToLight.normalize() * pLight->size;

						if(!pHull->pointInsideHull(pLight->center - hullToLight))
							maskShadow(pLight, pHull, !pHull->renderLightOverHull, 2.0f);
					}
				else
					for(unsigned int h = 0; h < numHulls; h++)
					{
						ConvexHull* pHull = static_cast<ConvexHull*>(regionHulls[h]);

						maskShadow(pLight, pHull, !pHull->renderLightOverHull, 2.0f);
					}

				// Render the hulls only for the hulls that had
				// there shadows rendered earlier (not out of bounds)
				for(unsigned int h = 0; h < numHulls; h++)
					static_cast<ConvexHull*>(regionHulls[h])->renderHull(2.0f);

				// Soft light angle fins (additional masking)
				pLight->renderLightSoftPortion();

				// Color reset
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

				// Now render that intermediate render Texture to the main render Texture
				if(pLight->isAlwaysUpdate())
				{
					lightTempTexture.display();

					switchComposition();
					glLoadIdentity();

					sf::Texture::bind(&lightTempTexture.getTexture());

					glBlendFunc(GL_ONE, GL_ONE);

					// Texture is upside-down for some reason, so draw flipped
					glBegin(GL_QUADS);
						glTexCoord2i(0, 1); glVertex2f(0.0f, 0.0f);
						glTexCoord2i(1, 1); glVertex2f(viewSize.x, 0.0f);
						glTexCoord2i(1, 0); glVertex2f(viewSize.x, viewSize.y);
						glTexCoord2i(0, 0); glVertex2f(0.0f, viewSize.y);
					glEnd();

					// Bloom render
					if(useBloom && pLight->intensity > 1.0f)
					{
						switchBloom();
						glLoadIdentity();

						sf::Texture::bind(&lightTempTexture.getTexture());

						glBlendFunc(GL_ONE, GL_ONE);
	
						// Bloom amount
						glColor4f(1.0f, 1.0f, 1.0f, pLight->intensity - 1.0f);

						// Texture is upside-down for some reason, so draw flipped
						glBegin(GL_QUADS);
							glTexCoord2i(0, 1); glVertex2f(0.0f, 0.0f);
							glTexCoord2i(1, 1); glVertex2f(viewSize.x, 0.0f);
							glTexCoord2i(1, 0); glVertex2f(viewSize.x, viewSize.y);
							glTexCoord2i(0, 0); glVertex2f(0.0f, viewSize.y);
						glEnd();

						glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					}
				}
				else
				{
					pLight->staticTexture->display();

					switchComposition();
					cameraSetup();

					sf::Texture::bind(&pLight->staticTexture->getTexture());

					glTranslatef(pLight->center.x - staticTextureOffset.x, pLight->center.y - staticTextureOffset.y, 0.0f);

					glBlendFunc(GL_ONE, GL_ONE);

					sf::Vector2u lightStaticTextureSize(pLight->staticTexture->getSize());
					const float lightStaticTextureWidth = static_cast<float>(lightStaticTextureSize.x);
					const float lightStaticTextureHeight = static_cast<float>(lightStaticTextureSize.y);

					glBegin(GL_QUADS);
						glTexCoord2i(0, 0); glVertex2f(0.0f, 0.0f);
						glTexCoord2i(1, 0); glVertex2f(lightStaticTextureWidth, 0.0f);
						glTexCoord2i(1, 1); glVertex2f(lightStaticTextureWidth, lightStaticTextureHeight);
						glTexCoord2i(0, 1); glVertex2f(0.0f, lightStaticTextureHeight);
					glEnd();

					// Bloom render
					if(useBloom && pLight->intensity > 1.0f)
					{
						switchBloom();
						cameraSetup();

						glTranslatef(pLight->center.x - staticTextureOffset.x, pLight->center.y - staticTextureOffset.y, 0.0f);

						sf::Texture::bind(&pLight->staticTexture->getTexture());

						glBlendFunc(GL_ONE, GL_ONE);
	
						// Bloom amount
						glColor4f(1.0f, 1.0f, 1.0f, pLight->intensity - 1.0f);

						glBegin(GL_QUADS);
							glTexCoord2i(0, 0); glVertex2f(0.0f, 0.0f);
							glTexCoord2i(1, 0); glVertex2f(lightStaticTextureWidth, 0.0f);
							glTexCoord2i(1, 1); glVertex2f(lightStaticTextureWidth, lightStaticTextureHeight);
							glTexCoord2i(0, 1); glVertex2f(0.0f, lightStaticTextureHeight);
						glEnd();

						glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					}
				}

				pLight->updateRequired = false;
			}
			else
			{
				switchComposition();

				// Render existing texture
				sf::Texture::bind(&pLight->staticTexture->getTexture());

				Vec2f staticTextureOffset(pLight->center - pLight->aabb.lowerBound);

				cameraSetup();
				glTranslatef(pLight->center.x - staticTextureOffset.x, pLight->center.y - staticTextureOffset.y, 0.0f);

				glBlendFunc(GL_ONE, GL_ONE);

				sf::Vector2u lightStaticTextureSize(pLight->staticTexture->getSize());
				const float lightStaticTextureWidth = static_cast<float>(lightStaticTextureSize.x);
				const float lightStaticTextureHeight = static_cast<float>(lightStaticTextureSize.y);

				glBegin(GL_QUADS);
					glTexCoord2i(0, 0); glVertex2f(0.0f, 0.0f);
					glTexCoord2i(1, 0); glVertex2f(lightStaticTextureWidth, 0.0f);
					glTexCoord2i(1, 1); glVertex2f(lightStaticTextureWidth, lightStaticTextureHeight);
					glTexCoord2i(0, 1); glVertex2f(0.0f, lightStaticTextureHeight);
				glEnd();

				// Bloom render
				if(useBloom && pLight->intensity > 1.0f)
				{
					switchBloom();
					cameraSetup();

					glTranslatef(pLight->center.x - staticTextureOffset.x, pLight->center.y - staticTextureOffset.y, 0.0f);

					sf::Texture::bind(&pLight->staticTexture->getTexture());

					glBlendFunc(GL_ONE, GL_ONE);
	
					// Bloom amount
					glColor4f(1.0f, 1.0f, 1.0f, pLight->intensity - 1.0f);

					glBegin(GL_QUADS);
						glTexCoord2i(0, 0); glVertex2f(0.0f, 0.0f);
						glTexCoord2i(1, 0); glVertex2f(lightStaticTextureWidth, 0.0f);
						glTexCoord2i(1, 1); glVertex2f(lightStaticTextureWidth, lightStaticTextureHeight);
						glTexCoord2i(0, 1); glVertex2f(0.0f, lightStaticTextureHeight);
					glEnd();

					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}

			regionHulls.clear();
		}

		// Emissive lights
		std::vector<qdt::QuadTreeOccupant*> visibleEmissiveLights;
		emissiveTree.queryRegion(viewAABB, visibleEmissiveLights);

		const unsigned int numEmissiveLights = visibleEmissiveLights.size();

		for(unsigned int i = 0; i < numEmissiveLights; i++)
		{
			EmissiveLight* pEmissive = static_cast<EmissiveLight*>(visibleEmissiveLights[i]);

			if(useBloom && pEmissive->intensity > 1.0f)
			{
				switchWindow();
				cameraSetup();
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				pEmissive->render();
			}
			else
			{
				switchComposition();
				cameraSetup();
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				pEmissive->render();
			}
		}

		bloomTexture.display();

		compositionTexture.display();

		switchWindow();
	}

	void LightSystem::buildLight(Light* pLight)
	{
		lightsToPreBuild.push_back(pLight);
	}

	void LightSystem::renderLightTexture()
	{
		Vec2f viewSize(viewAABB.getDims());

		// Translate by negative camera coordinates. glLoadIdentity will not work, probably
		// because SFML stores view transformations in the projection matrix
		glTranslatef(viewAABB.getLowerBound().x, -viewAABB.getLowerBound().y, 0.0f);

		sf::Texture::bind(&compositionTexture.getTexture());

		// Set up color function to multiply the existing color with the render texture color
		glBlendFunc(GL_DST_COLOR, GL_ZERO); // Seperate allows you to set color and alpha functions seperately

		glBegin(GL_QUADS);
			glTexCoord2i(0, 0); glVertex2f(0.0f, 0.0f);
			glTexCoord2i(1, 0); glVertex2f(viewSize.x, 0.0f);
			glTexCoord2i(1, 1); glVertex2f(viewSize.x, viewSize.y);
			glTexCoord2i(0, 1); glVertex2f(0.0f, viewSize.y);
		glEnd();

		if(useBloom)
		{
			sf::Texture::bind(&bloomTexture.getTexture());

			glBlendFunc(GL_ONE, GL_ONE);

			glBegin(GL_QUADS);
				glTexCoord2i(0, 0); glVertex2f(0.0f, 0.0f);
				glTexCoord2i(1, 0); glVertex2f(viewSize.x, 0.0f);
				glTexCoord2i(1, 1); glVertex2f(viewSize.x, viewSize.y);
				glTexCoord2i(0, 1); glVertex2f(0.0f, viewSize.y);
			glEnd();
		}

		// Reset blend function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		window->resetGLStates();
	}

	void LightSystem::debugRender()
	{
		// Set to a more useful-for-OpenGL projection
		Vec2f viewSize(viewAABB.getDims());

		glLoadIdentity();

		cameraSetup();

		// Render all trees
		lightTree.debugRender();
		emissiveTree.debugRender();
		hullTree.debugRender();

		glLoadIdentity();

		// Reset to SFML's projection
		window->resetGLStates();
	}
}
