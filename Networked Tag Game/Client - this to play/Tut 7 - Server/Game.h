/// <summary>
/// author - Adam Mcguigan 
/// Date - December 2022
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
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
	void run();

	std::string updatePlayersPos();
	std::string sendCheckedForPlayer();
	std::string CheckForCollisions();
	//std::string sendID();
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void getNumberOfPlayer(std::string& string);

	sf::Vector2f getPosFromServer(std::string& opponentPos, bool smaller);
	int len(std::string string);
	void split(std::string string, char seperator, bool smaller);

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture tile; // texture used for sfml logo
	sf::Sprite tileSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	Player player;
	Player Player2;
	Player Player3;


	sf::Clock Timer;
	sf::Time timer2;
	sf::Font m_font;
	sf::Text timerText;
	bool timerAlive = false;

	Client myClient;

	//Arrays to hold players 2 & 3 position
	std::string opponentPosPlayer2[3];
	std::string opponentPosPlayer3[3];

	int numberOfPlayer = 0;

	std::string check;
};

#endif // !GAME_HPP
