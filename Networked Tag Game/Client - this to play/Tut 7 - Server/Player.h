#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <sstream>

class Player
{
public:

	void init(std::string stringID);
	void render(sf::RenderWindow& win);
	void update();
	void update2();
	void update3();

	void playerMovement();
	void player2Movement();
	void player3Movement();
	void checkCollision(sf::RectangleShape opponent);
	void checkCollision2(sf::RectangleShape opponent);


	void setPlayerID(int ID);
	void setPosition(sf::Vector2f newPos);
	void setPlayerColor();
	void setText1();
	void setText2();
	void setText3();
	void checkWalls();
	sf::RectangleShape getPlayer();

	bool isIDSet();
	int speed = 5;
	int convertStringToID(std::string stringID);
	int getPlayerID();

	std::string getPlayerPosition();
	std::string getChecked();
	std::string CheckForCollision();



	bool player1Alive = false;
	bool player2Alive = false;
	bool player3Alive = false;

	//sf::Clock survivalClock1;
	//sf::Clock survivalClock2;
	//sf::Clock survivalClock3;

	//sf::Time survivalTime1;
	//sf::Time survivalTime2;
	//sf::Time survivalTime3;

	//sf::Text survivalText;

	sf::Text m_text;

private:

	sf::RectangleShape player;
	sf::Color color;
	sf::Font m_font;
	int playerID = -1;

	bool isColliding = false;
	bool IDSet = false;



};


