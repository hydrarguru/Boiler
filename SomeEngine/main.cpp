#include "Engine.h"


int main()
{
	sf::Font font;
	if (!font.loadFromFile("segoeui.ttf")) { return EXIT_FAILURE; }
	else { std::cout << "Font loaded!" << std::endl; }

	sf::Text text("Hello World", font, 24);
	

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Title");
	sf::Event event;

	//main loop
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		window.draw(text);
		window.display();


	}
	return 0;
}