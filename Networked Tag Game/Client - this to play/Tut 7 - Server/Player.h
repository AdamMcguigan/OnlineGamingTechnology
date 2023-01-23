#pragma once
#include <SFML/Graphics.hpp>
#include "Client.h"
class Player
{
public:
	Player();
	~Player();

	void playerMovement(sf::Event t_event, Client* t_client);
	void checkForChasePlayer();
	void CheckForPlayWalls();

	void update(sf::Time t_deltaTime, sf::Time t_deathTime);
	void render(sf::RenderWindow& m_window);

	int m_playerId = 0;

	bool m_isChasePlayerSet = false;
	bool m_isPlayerAlive = true;

	sf::RectangleShape m_playerShape;

private:
	void displaySurvivalTime(sf::Time t_time);

	bool m_timeDisplayed = false;
	float m_speed = 10.0f;

};

