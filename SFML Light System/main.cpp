#include "ls/lightsystem.h"
#include "ls/lightpoint.h"
#include "ls/utils.h"
#include <SFML/Graphics.hpp>

#include <sstream>
#include <cassert>
#include <cstdlib>

int main(int argc, char** args)
{
	sf::VideoMode vidMode;
	vidMode.width = 800;
	vidMode.height = 600;
	vidMode.bitsPerPixel = 32;
	assert(vidMode.isValid());

	sf::RenderWindow win;
	win.create(vidMode, "Light System");

	sf::View view;
	sf::Vector2u windowSize(win.getSize());
	view.setSize(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
	view.setCenter(view.getSize() / 2.0f);

	// ---------------------- Background Image ---------------------

	sf::Texture backgroundImage;

	if (!backgroundImage.loadFromFile("data/background.png"))
		std::abort();

	// Tiling background
	backgroundImage.setRepeated(true);

	sf::Sprite backgroundSprite(backgroundImage);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, vidMode.width * 2, vidMode.height * 2));
	backgroundSprite.setPosition(-400.0f, -400.0f);

	// --------------------- Light System Setup ---------------------

	ls::LightSystem ls(AABB(Vec2f(0.0f, 0.0f), Vec2f(static_cast<float>(vidMode.width), static_cast<float>(vidMode.height))), &win, "data/lightFin.png", "data/shaders/lightAttenuationShader.frag");

	// Create a light
	ls::LightPoint* testLight = new ls::LightPoint();
	testLight->intensity = 2.0f;
	testLight->center = Vec2f(200.0f, 200.0f);
	testLight->radius = 600.0f;
	testLight->size = 15.0f;
	testLight->spreadAngle = ls::pifTimes2;
	testLight->softSpreadAngle = 0.0f;
	testLight->calculateAABB();

	testLight->bleed = 0.4f;
	testLight->linearizeFactor = 0.2f;

	ls.addLight(testLight);

	testLight->setAlwaysUpdate(true);

	// Create a light
	ls::LightPoint* testLight2 = new ls::LightPoint();
	testLight2->center = Vec2f(200.0f, 200.0f);
	testLight2->radius = 500.0f;
	testLight2->size = 30.0f;
	testLight2->color.r = 0.5f;
	testLight2->intensity = 1.5f;
	testLight2->spreadAngle = ls::pifTimes2;
	testLight2->softSpreadAngle = 0.0f;
	testLight2->calculateAABB();

	ls.addLight(testLight2);

	testLight2->setAlwaysUpdate(false);

	// Create an emissive light
	ls::EmissiveLight* emissiveLight = new ls::EmissiveLight();

	sf::Texture text;

	if (!text.loadFromFile("data/emissive.png"))
		std::abort();

	emissiveLight->setTexture(&text);

	emissiveLight->setRotation(45.0f);

	emissiveLight->intensity = 1.3f;

	ls.addEmissiveLight(emissiveLight);

	emissiveLight->setCenter(Vec2f(500.0f, 500.0f));

	// Create a hull by loading it from a file
	ls::ConvexHull* testHull = new ls::ConvexHull();

	if (!testHull->loadShape("data/testShape.txt"))
		std::abort();

	// Pre-calculate certain aspects
	testHull->calculateNormals();
	testHull->calculateAABB();

	testHull->setWorldCenter(Vec2f(300.0f, 300.0f));

	testHull->renderLightOverHull = true;

	ls.addConvexHull(testHull);

	// ------------------------- Game Loop --------------------------

	sf::Event eventStructure;

	bool quit = false;

	ls.useBloom = true;

	while (!quit)
	{
		while (win.pollEvent(eventStructure))
			if (eventStructure.type == sf::Event::Closed)
			{
				quit = true;
				break;
			}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			view.move(sf::Vector2f(-1.0f, 0.0f));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			view.move(sf::Vector2f(1.0f, 0.0f));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			view.move(sf::Vector2f(0.0f, -1.0f));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			view.move(sf::Vector2f(0.0f, 1.0f));

		sf::Vector2f mousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
		//testLight2->IncCenter(ltbl::Vec2f(0.1f, 0.0f));
		// Update light
		testLight->setCenter(Vec2f(mousePos.x, mousePos.y));

		win.clear();

		win.setView(view);
		ls.setView(view);

		// Draw the background
		win.draw(backgroundSprite);

		// Calculate the lights
		ls.renderLights();

		// Draw the lights
		ls.renderLightTexture();

		ls.debugRender();

		win.display();
	}

	win.close();
}