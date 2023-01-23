#include "MainMenu.h"


/// <summary>
/// in main menu cpp we Used to get a reference to the font and  
/// load texture and setup sprite and text
/// for each button and positions on screen
/// </summary>
void MainMenu::initialise(sf::Font& font)
{
	m_topOffset = 100;
	m_verticalSpacing = 80;
	m_buttonWidth = 300;
	m_leftOffset = (580 - m_buttonWidth);
	m_buttonHeight = 70;
	int textDropOffset = 25;
	sf::String m_menuTexts[] = { "Play","Exit" };
	m_font = font;
	/// display error if button.png doesnt load properly
	if (!m_buttonTexture.loadFromFile("ASSETS/button.png"))
	{
		std::cout << "error with button file";
	}
	/// <summary>
	/// for loop to setup menu buttons in an array
	/// keeps them in a centre nicely laid out
	/// scales them to texture size so they look to scale
	/// </summary>
	for (int i = 0; i < m_optionCount; i++)
	{
		m_buttonSprites[i].setTexture(m_buttonTexture);
		m_buttonSprites[i].setPosition(m_leftOffset, m_verticalSpacing * i + m_topOffset);
		sf::Vector2u textureSize = m_buttonTexture.getSize();
		m_buttonSprites[i].setScale(m_buttonWidth / textureSize.x, m_buttonHeight / textureSize.y);
		/// <summary>
		// sets font up for the array of text shapes that display over the buttons
		/// </summary>
		m_buttonTexts[i].setFont(m_font);
		m_buttonTexts[i].setString(m_menuTexts[i]);
		m_buttonTexts[i].setFillColor(sf::Color::Black);
		m_buttonTexts[i].setCharacterSize(20);
		sf::FloatRect textSize = m_buttonTexts[i].getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.width) / 2;
		m_buttonTexts[i].setPosition(m_leftOffset + textOffset, m_verticalSpacing * i + m_topOffset + textDropOffset);
	}
}

/// <summary>
/// check current position of the mouse for intersection with
/// location of buttons using locations and offsets rather than rectangles
/// for intersection (create said so 'imaginary' columns and rows, then mouse x/y 
/// values are compared to see if they are intersecting columns' then rows' x/y values
/// </summary>
void MainMenu::update(sf::Window& window, int& t_gameMode)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mouseLocation;
		mouseLocation = sf::Mouse::getPosition(window);
		if (mouseLocation.x > m_leftOffset && mouseLocation.x < m_leftOffset + m_buttonWidth)
		{
			if (mouseLocation.y > m_topOffset && mouseLocation.y && mouseLocation.y < m_topOffset + m_buttonHeight)
			{
				t_gameMode = PLAY;	//new game
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing && mouseLocation.y < m_topOffset + m_verticalSpacing + m_buttonHeight)
			{
				window.close();		//exit
			}



		}
	}
}

/// <summary>
///  draw menu text over buttons
/// </summary>
void MainMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_optionCount; i++)
	{
		window.draw(m_buttonSprites[i]);
		window.draw(m_buttonTexts[i]);
	}
}