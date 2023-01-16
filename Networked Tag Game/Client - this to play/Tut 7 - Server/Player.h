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
		
	void playerMovement();
	void player2Movement();
	void player3Movement();
	void checkCollision(sf::RectangleShape opponent);

	void setPlayerID(int ID);
	void setPosition(sf::Vector2f newPos);
	void setPlayerColor();
	void setText1();
	void setText2();
	void setText3();
	void checkWalls();
	sf::RectangleShape getPlayer();

	bool isIDSet();

	int convertStringToID(std::string stringID);
	int getPlayerID();

	std::string getPlayerPosition();
	std::string getChecked();
	std::string CheckForCollision();

	
private:

	sf::RectangleShape player;
	sf::Color color;
	sf::Text m_text;
	sf::Font m_font;
	int playerID = -1;

	bool isColliding = false;
	bool IDSet = false;



};


