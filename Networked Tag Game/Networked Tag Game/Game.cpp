#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800, 800, 32u }, "Networked Tag Game" },
	m_exitGame{ false }
{
	setUpFontAndText();
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}


}

void Game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type)
		{
			m_window.close();
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	
}

void Game::render()
{
	m_window.clear();

	m_window.draw(m_scoreText);
	m_window.draw(m_livesText);

	m_window.display();
}

void Game::setUpFontAndText()
{
	if (!m_gooddogFont.loadFromFile("ASSETS\\FONTS\\gooddog.otf"))
	{
		// Error loading font file
		std::cout << "Error loading the font " << std::endl;
	}
	m_scoreText.setFont(m_gooddogFont);
	m_scoreText.setPosition(50.0f, 0.0f);
	m_scoreText.setString("HELLO CHECKING THE FONT IS WORKING ");

	m_livesText.setFont(m_gooddogFont);
	m_livesText.setPosition(50.0f, 0.0f);
}

