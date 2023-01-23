#include "Player.h"
#include <iostream>

//Player Constructor
Player::Player()
{
	m_playerShape.setSize(sf::Vector2f(50, 50));

	srand(time(NULL));

	int randX = rand() % 800 + 1;
	int randY = rand() % 800 + 1;

	m_playerShape.setPosition(randX, randY);

	m_playerShape.setFillColor(sf::Color::Magenta);
	m_playerShape.setOutlineColor(sf::Color::Black);
	m_playerShape.setOutlineThickness(1.0f);

}

Player::~Player()
{
}

//Player Movement - All movement handled on WASD
void Player::playerMovement(sf::Event t_event, Client* t_client)
{
	if (sf::Keyboard::W == t_event.key.code)
	{
		m_playerShape.move(0, -m_speed);
	}

	if (sf::Keyboard::S == t_event.key.code)
	{
		m_playerShape.move(0, m_speed);
	}

	if (sf::Keyboard::A == t_event.key.code)
	{
		m_playerShape.move(-m_speed, 0);
	}

	if (sf::Keyboard::D == t_event.key.code)
	{
		m_playerShape.move(m_speed, 0);
	}

	t_client->SendPosition(1, m_playerShape.getPosition());
}

//Check if the player is set to the Chase player
void Player::checkForChasePlayer()
{
	if (m_isChasePlayerSet == true)
	{
		m_playerShape.setFillColor(sf::Color::Red);
		m_playerShape.setPosition(380, 380);
		m_speed = 9.0f;
	}
}

//Checking the play area so that the player loops back around
void Player::CheckForPlayWalls()
{
	if (m_playerShape.getPosition().x > 880 + m_playerShape.getSize().x)
	{
		m_playerShape.setPosition(0 - m_playerShape.getSize().x, m_playerShape.getPosition().y);
	}

	if (m_playerShape.getPosition().x < 0 - m_playerShape.getSize().x)
	{
		m_playerShape.setPosition(880 + m_playerShape.getSize().x, m_playerShape.getPosition().y);
	}

	if (m_playerShape.getPosition().y < 0 - m_playerShape.getSize().y)
	{
		m_playerShape.setPosition(m_playerShape.getPosition().x, 880 + m_playerShape.getSize().y);
	}

	if (m_playerShape.getPosition().y > 880 + m_playerShape.getSize().y)
	{
		m_playerShape.setPosition(m_playerShape.getPosition().x, 0 - m_playerShape.getSize().y);
	}
	
}

//Update - Check for boundaries and if the player is caught, display the surived time
void Player::update(sf::Time t_deltaTime, sf::Time t_deathTime)
{
	if (m_isPlayerAlive)
	{
		CheckForPlayWalls();

	}

	if (m_timeDisplayed == false)
	{
		if (m_isPlayerAlive == false)
		{
			displaySurvivalTime(t_deathTime);
		}
	}
}

void Player::render(sf::RenderWindow& m_window)
{
	m_window.draw(m_playerShape);
}

void Player::displaySurvivalTime(sf::Time t_time)
{
	m_timeDisplayed = true;
	std::cout << "player died at 9" << t_time.asSeconds() << std::endl;
}




