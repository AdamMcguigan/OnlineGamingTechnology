#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Globals.h"
/// <summary>
/// This is main menu class that allows us to start in the menu of the game 
/// </summary>
class MainMenu
{
	/// <summary>
	/// Number of buttons on our menu
	/// </summary>
	static const int m_optionCount = 2;
	/// <summary>
	/// button background
	/// </summary>
	sf::Texture m_buttonTexture;
	/// <summary>
	/// array of sprites used to display buttons
	/// </summary>
	sf::Sprite m_buttonSprites[m_optionCount];
	/// <summary>
	/// local refrence to font used by whole game
	/// </summary>
	sf::Font m_font;
	/// <summary>
	///  array of text objects for text on buttons
	/// </summary>
	sf::Text m_buttonTexts[m_optionCount];

	/// top left of area used for menu
	float m_topOffset;
	/// top left of area used for menu
	float m_leftOffset;
	/// gap in pixels between tops of buttons
	float m_verticalSpacing;
	/// width in pixels of all buttons
	float m_buttonWidth;
	/// height of button in pixels must be less than vertical spacing
	float m_buttonHeight;

public:
	void initialise(sf::Font&);
	void draw(sf::RenderWindow&);
	void update(sf::Window&, int& t_gameMode);

};