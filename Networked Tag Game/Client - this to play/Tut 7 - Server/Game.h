#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Client.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run(Client& t_client);
	void assignPlayer(int t_playerID);
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void selectChasePlayer();
	void setupFontAndText();
	void checkForCollisions();

	sf::Time survivalTime;
	sf::Clock survivalClock;

	Client* m_client = nullptr;

	Player m_playerOne;
	sf::Vector2f m_playerOnePos;
	bool isPlayerTwoSet = false;

	Player m_playerTwo;
	sf::Vector2f m_playerTwoPos;
	bool isPlayerOneSet = false;

	Player m_playerThree;
	sf::Vector2f m_playerThreePos;
	bool isPlayerThreeSet = false;

	sf::Texture tile; // texture used for background
	sf::Sprite tileSprite; // sprite used for background

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_font; // font used by message
	sf::Text m_chasePlayerText; // text used for message on screen
	
	//This is used to display how long each character has survived
	sf::Text m_SurvivalTime[3];

	sf::Text chasePlayerWonText;

	int m_resetCounter = 0;


	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

