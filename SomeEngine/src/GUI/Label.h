#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

class Label
{
private:
	sf::Text _labelText;
public:
	/*
	 * @param posX: x coordinate of the box.
	 * @param posY: y coordinate of the box.
	 * @param text: Text content.
	 * @param font: Font.
	 * @param labelSize: Size of text.
	 * @param labelColor: Fill color for the text.
	 * @param outlineColor: The outline color of the text.
	 */
	Label(
		float posX, float posY,
		std::string text, sf::Font* font,
		unsigned int labelSize,
		sf::Color labelColor, sf::Color outlineColor
		);
	/*
	* Text has white fill color with a black outline color
	* @param posX: x coordinate of the box.
	* @param posY: y coordinate of the box.
	* @param text: Text content.
	* @param font: Font.
	* @param labelSize: Size of text.
	*/
	Label
	(
		float posX, float posY,
		std::string text, sf::Font* font,
		unsigned int labelSize
	);



	~Label();
	//Functions
	void Render(sf::RenderTarget* target);
};

