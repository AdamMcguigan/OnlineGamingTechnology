#include "Player.h"

void Player::init(std::string stringID)
{
	setPlayerID(convertStringToID(stringID));

	setPlayerColor();

	player.setSize(sf::Vector2f(50, 50));
	player.setPosition(sf::Vector2f(20, 100));


	if (!m_font.loadFromFile("ASSETS/FONTS/Pixellari.ttf"))
	{
		std::cout << "failed loading font " << std::endl;
	}

	m_text.setFont(m_font);
	m_text.setCharacterSize(70.0f);
	m_text.setPosition(10, 10);

	if (playerID == 0)
	{
		player.setPosition(20, 100);
	}

	//this is for testing with another client started on local PC
	else if (playerID == 1)
	{
		player.setPosition(200, 600);
	}

	else if (playerID == 2)
	{
		player.setPosition(500, 300);
	}
}

void Player::render(sf::RenderWindow& win)
{
	win.draw(player);
	win.draw(m_text);
}

void Player::update()
{
	if (playerID == 0)
	{
		playerMovement();
		setText1();

	}

	//this is for testing with another client started on local PC
	else if (playerID == 1)
	{
		player2Movement();
		setText2();

	}

	else if (playerID == 2)
	{
		player3Movement();
		setText3();

	}
}

void Player::playerMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.move(0, -10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player.move(0, 10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.move(-10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.move(10, 0);
	}
}

void Player::player2Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.move(0, -10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.move(0, 10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.move(-10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(10, 0);
	}
}

void Player::player3Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		player.move(0, -10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		player.move(0, 10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		player.move(-10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		player.move(10, 0);
	}
}

void Player::setText1()
{
	m_text.setString("Your Colour is Green");

}

void Player::setText2()
{
	m_text.setString("Your Colour is Blue");

}

void Player::setText3()
{
	m_text.setString("Your Colour is Magenta");

}
//This Method is checking for collision between players
void Player::checkCollision(sf::RectangleShape opponent)
{
	if (player.getGlobalBounds().intersects(opponent.getGlobalBounds()))
	{
		player.setFillColor(sf::Color::Yellow);
		std::cout << "Player: " << getPlayerID() << "is colliding" << std::endl;
		isColliding = true;
	}

	else
	{
		player.setFillColor(color);
		isColliding = false;
	}
}

//This Get Method is returning the players body or rectangle shape.
sf::RectangleShape Player::getPlayer()
{
	return player;
}

//This method returns a string of the current players X and Y positions
std::string Player::getPlayerPosition()
{
	return std::to_string(getPlayerID()) + "," + std::to_string(player.getPosition().x) + "," + std::to_string(player.getPosition().y);
}

//String method to return if collision happened or not
std::string Player::CheckForCollision()
{
	return std::to_string(isColliding); // 1 is colliding , 0 is not 
}

//Set method to set the players position
void Player::setPosition(sf::Vector2f newPos)
{
	player.setPosition(newPos);
}

//Method to set the players colors as they join
void Player::setPlayerColor()
{
	switch (playerID)
	{
	case 0:
		color = sf::Color::Green;
		break;
	case 1:
		color = sf::Color::Blue;
		break;
	case 2:
		color = sf::Color::Magenta;
		break;
	default:
		color = sf::Color::Red;
		break;
	}

	player.setFillColor(color);
}

//Method to set the players ID and to set their color
void Player::setPlayerID(int ID)
{
	playerID = ID;
	setPlayerColor();
	IDSet = true;
}

//Returns the players ID 
int Player::getPlayerID()
{
	return playerID;
}

//Method to change parameters in a string to an ID
int Player::convertStringToID(std::string stringID)
{
	std::istringstream stream(stringID);
	int result;
	stream >> result;
	return result;
}

bool Player::isIDSet()
{
	return IDSet;
}

std::string Player::getChecked()
{
	return std::to_string(10);
}


