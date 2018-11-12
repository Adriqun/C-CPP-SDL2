#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	int width = 900;
	int height = 900;

	RenderWindow window(VideoMode(width, height, 32), "GLSL Mandelbrot set plotter");

	Shader fragment_shader;
	if (!fragment_shader.loadFromFile("mandelbrot.frag", Shader::Fragment)) cout << "Frag shader error :(" << endl;

	Texture texture; texture.create(width, height);
	Sprite sprite; sprite.setTexture(texture);
	float X0 = 0;
	float Y0 = 0;
	float zoom = 1;
	float maxIteration = 900;

	fragment_shader.setUniform("texture", texture);
	fragment_shader.setUniform("X0", X0);
	fragment_shader.setUniform("Y0", Y0);
	fragment_shader.setUniform("zoom", zoom);
	fragment_shader.setUniform("maxIteration", maxIteration);

	Clock deltaTime;
	float dt = 0.01;

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Z))
			zoom += (1 * zoom)*dt;
		if (Keyboard::isKeyPressed(Keyboard::S))
			zoom -= (1 * zoom)*dt;
		if (Keyboard::isKeyPressed(Keyboard::Left))
			X0 -= (1 / zoom)*dt;
		if (Keyboard::isKeyPressed(Keyboard::Right))
			X0 += (1 / zoom)*dt;
		if (Keyboard::isKeyPressed(Keyboard::Up))
			Y0 -= (1 / zoom)*dt;
		if (Keyboard::isKeyPressed(Keyboard::Down))
			Y0 += (1 / zoom)*dt;
		if (Keyboard::isKeyPressed(Keyboard::Q))
			maxIteration -= 500 * dt;
		if (Keyboard::isKeyPressed(Keyboard::D))
			maxIteration += 500 * dt;
		fragment_shader.setUniform("texture", texture);
		fragment_shader.setUniform("X0", X0);
		fragment_shader.setUniform("Y0", Y0);
		fragment_shader.setUniform("zoom", zoom);
		fragment_shader.setUniform("maxIteration", maxIteration);
		window.clear();
		window.draw(sprite, &fragment_shader);
		window.display();

		dt = deltaTime.restart().asSeconds();
	}
}