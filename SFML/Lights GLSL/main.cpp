// Author: Adrian Michalek
// Goal: Pure lights done with glsl
// Date: 01.11.2018 (Code copied from AG2 game from ~2017)
#include <SFML/Graphics.hpp>

int main()
{
	const int screen_w = 800;
	const int screen_h = 600;
	sf::RenderWindow window;
	window.create(sf::VideoMode(screen_w, screen_h), "Light Example", sf::Style::Titlebar | sf::Style::Close);

	const std::string vertexShader = \
		"void main()" \
		"{" \
		"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" \
		"gl_TexCoord[ 0 ] = gl_TextureMatrix[ 0 ] * gl_MultiTexCoord0;" \
		"gl_FrontColor = gl_Color;" \
		"}";

	const std::string fragmentShader = \
		"uniform sampler2D texture;" \
		"uniform vec2 resolution;" \
		"uniform vec4 ambientColor;" \
		"uniform float addAlpha = 1.0;" \
		"uniform float globalAlpha = 0.0;" \
		"uniform vec4 hiddenColor = vec4(1.0, 1.0, 1.0, 1.0);" \
		"uniform int arraySize = 0;" \
		"uniform float time;" \
		"uniform vec2 positions[ 12 ];" \
		"uniform vec4 lightColors[ 12 ];" \
		"uniform float radii[ 12 ];" \
		"void main()" \
		"{" \
		"vec3 light;" \
		"for( int i = 0; i < arraySize; i++ )" \
		"{" \
		"vec2 position = positions[ i ] /resolution.xx;" \
		"float maxDistance = radii[ i ] +0.005 *sin( time );" \
		"float distance = distance( gl_FragCoord.xy /resolution.xx, position );" \
		"float value = 1.0 - smoothstep( -0.2, maxDistance, distance );" \
		"light += (lightColors[ i ].rgb *lightColors[ i ].a *clamp( value, 0.0, 1.0 ));" \
		"}" \
		"vec4 pixel = texture2D( texture, gl_TexCoord[0].xy );" \
		"vec3 ambient = pixel.rgb *ambientColor.rgb *ambientColor.a;" \
		"vec3 intensity = ambient +light;" \
		"vec3 final = pixel.rgb *hiddenColor.rgb *intensity;" \
		"gl_FragColor = vec4( final, pixel.a *addAlpha *globalAlpha );" \
		"}";

	sf::Shader shader;
	if (shader.loadFromMemory(vertexShader, fragmentShader))
	{
		shader.setUniform("texture", sf::Shader::CurrentTexture);
		shader.setUniform("resolution", sf::Glsl::Vec2(screen_w, screen_h));
		shader.setUniform("ambientColor", sf::Glsl::Vec4(0.0, 0.0, 0.3, 0.5)); // 0.0, 0.0, 0.3, 0.5 - navy blue.
		shader.setUniform("globalAlpha", 1.0f);
	}

	sf::Texture bg;
	bg.loadFromFile("bg.png");
	sf::Sprite background;
	background.setTexture(bg);
	background.setPosition(0, 0);
	background.setScale(0.4, 0.4);

	std::vector<float> radii;
	std::vector<sf::Glsl::Vec4> colors;
	std::vector<sf::Glsl::Vec2> positions;
	radii.push_back(0.3);
	colors.push_back(sf::Glsl::Vec4(1.0, 0.8, 0.8, 0.8));
	positions.push_back(sf::Glsl::Vec2(0.5, 0.5));

	sf::Clock clock;
	sf::Time frameTime, time;

	bool quit = false;
	sf::Event event;
	while (!quit)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				quit = true;
				break;
			}

			if (event.type == sf::Event::MouseMoved)
			{
				positions[0].x = event.mouseMove.x;
				positions[0].y = screen_h - event.mouseMove.y;
			}
		}
			
		window.clear();

		frameTime = clock.restart();
		time += frameTime;

		int size = radii.size();
		shader.setUniform("arraySize", size);
		shader.setUniform("time", 10 * time.asSeconds());
		shader.setUniformArray("radii", &std::vector<float>(radii.begin(), radii.begin() + size)[0], size);
		shader.setUniformArray("lightColors", &std::vector<sf::Glsl::Vec4>(colors.begin(), colors.begin() + size)[0], size);
		shader.setUniformArray("positions", &std::vector<sf::Glsl::Vec2>(positions.begin(), positions.begin() + size)[0], size);
		shader.setUniform("addAlpha", 1.0f);

		// Draw.
		window.draw(background, &shader);

		window.display();
	}

	window.close();

	return 0;
}