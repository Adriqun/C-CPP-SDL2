// Author: Adrian Michalek
// Goal: Pure lights done with glsl
// Date: 01.11.2018 (Code copied from AG2 game from ~2017)
#include <SFML/Graphics.hpp>
#include "core.h"
#include "fpsconsole.h"
#include <fstream>

int main(int argc, char** argv)
{
	cmm::Core core;
	core.create("Lights");
	const int num_of_lights = std::stoi(argv[1]);

	const std::string vertexShader = \
		"void main()" \
		"{" \
		"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" \
		"gl_TexCoord[ 0 ] = gl_TextureMatrix[ 0 ] * gl_MultiTexCoord0;" \
		"gl_FrontColor = gl_Color;" \
		"}";

	const std::string fragmentShader = \
		"uniform sampler2D texture;" \
		"const vec2 resolution = vec2(" + std::to_string(core.getWidth()) + "," + std::to_string(core.getHeight()) + ");" \
		"const vec4 ambientColor = vec4(0.0, 0.0, 0.3, 0.5);" \
		"uniform float addAlpha = 1.0;" \
		"uniform float globalAlpha = 0.0;" \
		"uniform int arraySize = 0;" \
		"uniform vec2 positions[" + std::to_string(num_of_lights) + "];" \
		"uniform vec4 lightColors[" + std::to_string(num_of_lights) + "];" \
		"uniform float maxDistances[" + std::to_string(num_of_lights) + "];" \
		"void main()" \
		"{" \
		"vec3 light;" \
		"for(int i = 0; i < arraySize; ++i)" \
		"{" \
		"float distance = distance(gl_FragCoord.xy /resolution.xx, positions[i]);" \
		"float value = 1.0 - smoothstep(-0.2, maxDistances[i], distance);" \
		"light += (lightColors[ i ].rgb *lightColors[ i ].a *clamp( value, 0.0, 1.0 ));" \
		"}" \
		"vec4 pixel = texture2D( texture, gl_TexCoord[0].xy );" \
		"vec3 ambient = pixel.rgb *ambientColor.rgb *ambientColor.a;" \
		"vec3 intensity = ambient +light;" \
		"vec3 final = pixel.rgb * vec3(1.0, 1.0, 1.0) * intensity;" \
		"gl_FragColor = vec4( final, pixel.a *addAlpha *globalAlpha );" \
		"}";

	sf::Shader shader;
	if (shader.loadFromMemory(vertexShader, fragmentShader))
	{
		shader.setUniform("texture", sf::Shader::CurrentTexture);
		//shader.setUniform("resolution", sf::Glsl::Vec2(core.getWidth(), core.getHeight()));
		//shader.setUniform("ambientColor", sf::Glsl::Vec4(0.0, 0.0, 0.3, 0.5)); // 0.0, 0.0, 0.3, 0.5 - navy blue.
		shader.setUniform("globalAlpha", 1.0f);
	}

	sf::Texture bg;
	bg.loadFromFile("bg.png");
	sf::Sprite background;
	background.setTexture(bg);
	background.setPosition(0, 0);
	background.setScale(core.getWidth() / bg.getSize().x, core.getHeight() / bg.getSize().y);

	std::vector<float> radii;
	std::vector<float> maxDistances;
	std::vector<sf::Glsl::Vec4> colors;
	std::vector<sf::Glsl::Vec2> positions;
	std::vector<sf::Glsl::Vec2> gpositions;
	//radii.push_back(0.3);
	//colors.push_back(sf::Glsl::Vec4(1.0, 0.8, 0.8, 0.8));
	//positions.push_back(sf::Glsl::Vec2(0.5, 0.5));

	srand(time(nullptr));

	for (int i = 0; i < num_of_lights; ++i)
	{
		radii.push_back(static_cast<float>(rand() % 50 + 150) / 1000);
		float r = static_cast<float>(rand() % 0xFF) / 0xFF;
		float g = static_cast<float>(rand() % 0xFF) / 0xFF;
		float b = static_cast<float>(rand() % 0xFF) / 0xFF;
		float a = 2.0f;
		colors.push_back(sf::Glsl::Vec4(r, g, b, a));
		float x = static_cast<float>(rand() % 100) / 100;
		float y = static_cast<float>(rand() % 100) / 100;
		positions.push_back(sf::Glsl::Vec2(core.getWidth()*x, core.getHeight() - core.getHeight()*y));
	}

	for (auto &it : radii)
	{
		maxDistances.push_back(0.0f);
		gpositions.push_back(sf::Glsl::Vec2(0.0f, 0.0f));
	}
		

	sf::Clock clock;
	sf::Time frameTime, time;
	cmm::FPSConsole fps;

	std::vector <float> mean;
	int counter = 0;
	bool quit = false;
	while (core.open)
	{
		// clear
		core.clear();

		// events, mouse, keyboard
		while (core.isEvent())
		{
			if (core.getEvent().type == sf::Event::Closed)
				core.open = false;

			if (core.getEvent().type == sf::Event::MouseMoved)
			{
				//positions[0].x = core.getEvent().mouseMove.x;
				//positions[0].y = core.getHeight() - core.getEvent().mouseMove.y;
			}
		}

		frameTime = clock.restart();
		time += frameTime;

		int size = radii.size();
		for (int i = 0; i < size; ++i)
		{
			gpositions[i].x = positions[i].x / core.getWidth();
			gpositions[i].y = positions[i].y / core.getWidth();
			maxDistances[i] = radii[i] + 0.005 * sin(10 * time.asSeconds());
		}

		shader.setUniform("arraySize", size);
		//shader.setUniform("time", 10 * time.asSeconds());
		shader.setUniformArray("maxDistances", &std::vector<float>(maxDistances.begin(), maxDistances.begin() + size)[0], size);
		shader.setUniformArray("lightColors", &std::vector<sf::Glsl::Vec4>(colors.begin(), colors.begin() + size)[0], size);
		shader.setUniformArray("positions", &std::vector<sf::Glsl::Vec2>(gpositions.begin(), gpositions.begin() + size)[0], size);
		shader.setUniform("addAlpha", 1.0f);

		// Draw.
		core.getWindow()->draw(background, &shader);

		fps.mechanics(core.getElapsedTime());
		if (fps.timePassed())
		{
			mean.push_back(fps.getFPS());
			printf("%d. Fps: %f\n", counter, mean[mean.size() - 1]);
			++counter;
			if (counter == 30) // 30sec
				break;
		}

		core.display();
	}

	float sum = 0;
	mean.front() = mean.back();
	mean.pop_back();
	mean.front() = mean.back();
	for (auto &it : mean)
		sum += it / mean.size();

	std::fstream ofile;
	ofile.open("result.txt", std::ios::app);
	ofile << "Number of Lights: " << num_of_lights << " -> Mean: " << sum << "\n";
	ofile.close();

	core.close();
	return 0;
}