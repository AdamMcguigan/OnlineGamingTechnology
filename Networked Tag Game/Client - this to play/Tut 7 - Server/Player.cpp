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
	//survivalText.setFont(m_font);
	//survivalText.setCharacterSize(70.0f);
	//survivalText.setPosition(100, 100);

	m_text.setFont(m_font);
	m_text.setCharacterSize(70.0f);
	m_text.setPosition(10, 10);

	if (playerID == 0)
	{
		player.setPosition(20, 100);
		player1Alive = true;
	}

	//this is for testing with another client started on local PC
	else if (playerID == 1)
	{
		player.setPosition(200, 600);
		player2Alive = true;
		

	}

	else if (playerID == 2)
	{
		player.setPosition(500, 300);
		player3Alive = true;
	

	}

}

void Player::render(sf::RenderWindow& win)
{
	win.draw(player);
	//win.draw(survivalText);
	win.draw(m_text);
}

void Player::update()
{
	if (playerID == 0 && player1Alive == true)
	{
		playerMovement();
		setText1();
	}
	//this is for testing with another client started on local PC
	checkWalls();
}

void Player::update2()
{
	if(player2Alive == true)
	{
		player2Movement();
		setText2();
		//survivalText.setString("survival time: " + std::to_string(survivalTime2.asSeconds()));
	}
	if (player3Alive == true)
	{
		player3Movement();
		setText3();
		//	survivalText.setString("survival time: " + std::to_string(survivalTime3.asSeconds()));

	}
	checkWalls();
}

void Player::update3()
{
	if (playerID == 1 && player3Alive == true)
	{
		player3Movement();
		setText3();
	//	survivalText.setString("survival time: " + std::to_string(survivalTime3.asSeconds()));

	}
	checkWalls();
}

void Player::playerMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.move(0, -speed -2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player.move(0, speed +2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.move(-speed -2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.move(speed +2, 0);
	}
}

void Player::player2Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.move(0, -speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.move(0, speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.move(-speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(speed, 0);
	}
}

void Player::player3Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		player.move(0, -speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		player.move(0, speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		player.move(-speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		player.move(speed, 0);
	}
}

void Player::checkWalls()
{
	if (player.getPosition().x > 880 + player.getSize().x)
	{
		player.setPosition(0 - player.getSize().x,player.getPosition().y);
	}
	if (player.getPosition().x < 0 - player.getSize().x)
	{
		player.setPosition(880 + player.getSize().x, player.getPosition().y);
	}
	if (player.getPosition().y < 0 - player.getSize().y)
	{
		player.setPosition(player.getPosition().x, 880 + player.getSize().y);
	}
	if (player.getPosition().y > 880 + player.getSize().y)
	{
		player.setPosition(player.getPosition().x, 0 - player.getSize().y);
	}


}

void Player::setText1()
{
	m_text.setString("You are chaser");

}

void Player::setText2()
{
	m_text.setString("You are not chaser");

}

void Player::setText3()
{
	m_text.setString("You are not chaser");

}

//This Method is checking for collision between players
void Player::checkCollision(sf::RectangleShape opponent)
{
	if (player.getGlobalBounds().intersects(opponent.getGlobalBounds()))
	{
		player.setFillColor(sf::Color::Yellow);
		std::cout << "Player: " << getPlayerID() << "is colliding" << std::endl;
		isColliding = true;
		player2Alive = false;
	}

	else
	{
		player.setFillColor(color);
		isColliding = false;
	}
}



//This Method is checking for collision between players
void Player::checkCollision2(sf::RectangleShape opponent)
{
	if (player.getGlobalBounds().intersects(opponent.getGlobalBounds()))
	{
		player.setFillColor(sf::Color::Yellow);
		std::cout << "Player: " << getPlayerID() << "is colliding" << std::endl;
		isColliding = true;
		player3Alive = false;

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


