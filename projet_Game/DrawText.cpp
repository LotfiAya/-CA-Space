#include <SFML/Graphics.hpp>

#include "DrawText.h"
#include <iostream>

using namespace std; 
//void draw_text(short i_x, short i_y, const std::string& i_text, sf::RenderWindow& i_window, const sf::Texture& i_font_texture)
//{
//	short character_x = i_x;
//	short character_y = i_y;
//
//	unsigned char character_height = i_font_texture.getSize().y;
//	//There are 96 characters in the font texture.
//	unsigned char character_width = i_font_texture.getSize().x / 96;
//
//	sf::Sprite character_sprite(i_font_texture);
//
//	for (std::string::const_iterator a = i_text.begin(); a != i_text.end(); a++)
//	{
//		if ('\n' == *a)
//		{
//			character_x = i_x;
//			character_y += character_height;
//
//			continue;
//		}
//
//		character_sprite.setPosition(character_x, character_y);
//		character_sprite.setTextureRect(sf::IntRect(character_width * (*a - 32), 0, character_width, character_height));
//
//		character_x += character_width;
//
//		i_window.draw(character_sprite);
//	}
//}

void draw_text(short i_x, short i_y, const std::string& i_text, sf::RenderWindow& i_window, const sf::Color& i_color)
{
	sf::Font font; 

	if (!font.loadFromFile("Resources/Fonts/Horizon.otf"))
	{
		cout << "ERROR::FONT_LOANDING  ! \n"; 
	}

	sf::Text text;
	text.setFont(font); 
	text.setString(i_text); 
	text.setCharacterSize(10); 
	text.setPosition(i_x, i_y); 
	text.setFillColor(i_color); 
	i_window.draw(text); 
}