
#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 880, 880, 32U }, "Networked Tag Game" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run(Client& t_client)
{
	m_client = &t_client;

	selectChasePlayer();
	survivalClock.restart();
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps


	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
void Game::assignPlayer(int t_playerID)
{
	//setting player 1 bools and setting player one to active
	if (t_playerID == 0)
	{
		isPlayerOneSet = true;
		m_playerOne.m_isPlayerAlive = true;
	}

	//setting player 2 bools and setting player two to active
	else if (t_playerID == 1)
	{
		isPlayerTwoSet = true;
		m_playerTwo.m_isPlayerAlive = true;
	}

	//setting player 3 bools and setting player three to active
	else if (t_playerID == 2)
	{
		isPlayerThreeSet = true;
		m_playerThree.m_isPlayerAlive = true;
	}

}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{

			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	//Check if All players have joined game, when true set players to alive and allow movement
	if (m_client->readyToPlay == true)
	{
		if (isPlayerThreeSet)
		{
			if (m_playerThree.m_isPlayerAlive)
			{
				m_playerThree.playerMovement(t_event, m_client);
			}
		}

		else if (isPlayerOneSet)
		{
			if (m_playerOne.m_isPlayerAlive)
			{
				m_playerOne.playerMovement(t_event, m_client);
			}
		}

		else if (isPlayerTwoSet)
		{
			if (m_playerTwo.m_isPlayerAlive)
			{
				m_playerTwo.playerMovement(t_event, m_client);
			}
		}
	}

	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	//Checking if the client is ready to play and time is less than 60
	if (m_client->readyToPlay == true && m_resetCounter < 60)
	{
		survivalClock.restart();
		m_resetCounter++;
	}

	if (m_client->readyToPlay == true)
	{
		survivalTime = survivalClock.getElapsedTime();

		if (isPlayerOneSet)
		{
			m_playerOne.update(t_deltaTime, survivalTime);
			m_playerTwo.m_playerShape.setPosition(m_client->playerTwoPos);
			m_playerThree.m_playerShape.setPosition(m_client->playerThreePos);
		}

		if (isPlayerTwoSet)
		{
			m_playerTwo.update(t_deltaTime, survivalTime);
			m_playerOne.m_playerShape.setPosition(m_client->playerOnePos);
			m_playerThree.m_playerShape.setPosition(m_client->playerThreePos);
		}

		if (isPlayerThreeSet)
		{
			m_playerThree.update(t_deltaTime, survivalTime);
			m_playerOne.m_playerShape.setPosition(m_client->playerOnePos);
			m_playerTwo.m_playerShape.setPosition(m_client->playerTwoPos);
		}

		//Checking if player one is the chaser
		if (m_client->chasePlayerNumber == 1)
		{
			m_playerOne.m_playerShape.setFillColor(sf::Color::Red);
		}

		//Checking if player two is the chaser
		if (m_client->chasePlayerNumber == 2)
		{
			m_playerTwo.m_playerShape.setFillColor(sf::Color::Red);
		}

		//Checking if player three is the chaser
		if (m_client->chasePlayerNumber == 3)
		{
			m_playerThree.m_playerShape.setFillColor(sf::Color::Red);
		}

		m_resetCounter++;

		//set collisions active after 5 seconds of game time 
		if (survivalClock.getElapsedTime().asSeconds() > 5)
		{
			checkForCollisions();
		}

		m_chasePlayerText.setString("Red is the chaser\nTime elapsed: " + std::to_string(survivalClock.getElapsedTime().asSeconds()));

		

	}


	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	//Drawing background and chase text
	m_window.draw(tileSprite);
	m_window.draw(m_chasePlayerText);

	//Drawing players
	m_playerOne.render(m_window);
	m_playerTwo.render(m_window);
	m_playerThree.render(m_window);

	//Drawing the survival times for each player
	for (int i = 0; i < 3; i++)
	{
		m_window.draw(m_SurvivalTime[i]);
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	//Loading background
	if (!tile.loadFromFile("ASSETS/tile.png"))
	{
		std::cout << "failed loading font " << std::endl;
	}

	//Loading font file
	if (!m_font.loadFromFile("ASSETS\\FONTS\\Pixellari.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	//Text for chase Player
	m_chasePlayerText.setFont(m_font);
	m_chasePlayerText.setString("Red is the chaser\nTime elapsed: " + std::to_string(survivalClock.getElapsedTime().asSeconds()));
	m_chasePlayerText.setStyle(sf::Text::Bold);
	m_chasePlayerText.setPosition(20.0f, 20.0f);
	m_chasePlayerText.setCharacterSize(30U);
	m_chasePlayerText.setOutlineColor(sf::Color::White);
	m_chasePlayerText.setFillColor(sf::Color::Transparent);
	m_chasePlayerText.setOutlineThickness(1.0f);

	//Setting Values for font
	for (int i = 0; i < 3; i++)
	{
		m_SurvivalTime[i].setFont(m_font);
		m_SurvivalTime[i].setString("Player has survived for: ");
		m_SurvivalTime[i].setStyle(sf::Text::Bold);
		m_SurvivalTime[i].setCharacterSize(30U);
		m_SurvivalTime[i].setOutlineColor(sf::Color::White);
		m_SurvivalTime[i].setFillColor(sf::Color::Transparent);
		m_SurvivalTime[i].setOutlineThickness(1.0f);
	}

	//Survival Time Text Position
	m_SurvivalTime[0].setPosition(20.0f, 780.0f);
	m_SurvivalTime[1].setPosition(20.0f, 810.0f);
	m_SurvivalTime[2].setPosition(20.0f, 840.0f);

	//Background
	tileSprite.setTexture(tile);

}


void Game::selectChasePlayer()
{
	//Setting the colors for each of the players 
	m_playerOne.m_playerShape.setFillColor(sf::Color::Green);
	m_playerTwo.m_playerShape.setFillColor(sf::Color::Blue);
	m_playerThree.m_playerShape.setFillColor(sf::Color::Magenta);

	//Setting values if Player 1 is the chase player
	if (m_client->chasePlayerNumber == 1)
	{
		srand(time(NULL));
		int randX = rand() % 800 + 1;
		int randX2 = rand() % 600 + 1;
		int randX3 = rand() % 400 + 1;

		m_playerOne.m_isChasePlayerSet = true;
		m_playerTwo.m_playerShape.setPosition(200, 200);
		m_playerThree.m_playerShape.setPosition(randX, 200);
		m_playerOne.m_playerShape.setFillColor(sf::Color::Red);
		m_playerOne.m_playerShape.setPosition(randX3, 800);
	}

	//Setting values if Player 2 is the chase player
	if (m_client->chasePlayerNumber == 2)
	{
		srand(time(NULL));
		int randX = rand() % 800 + 1;
		int randX2 = rand() % 600 + 1;
		int randX3 = rand() % 400 + 1;

		m_playerTwo.m_isChasePlayerSet = true;
		m_playerOne.m_playerShape.setPosition(200, 200);
		m_playerThree.m_playerShape.setPosition(randX2, 200);
		m_playerTwo.m_playerShape.setFillColor(sf::Color::Red);
		m_playerTwo.m_playerShape.setPosition(randX3, 800);
	}

	//Setting values if Player 3 is the chase player
	if (m_client->chasePlayerNumber == 3)
	{
		srand(time(NULL));
		int randX = rand() % 800 + 1;
		int randX2 = rand() % 600 + 1;
		int randX3 = rand() % 400 + 1;

		m_playerThree.m_isChasePlayerSet = true;
		m_playerOne.m_playerShape.setPosition(200, 200);
		m_playerTwo.m_playerShape.setPosition(randX2, 200);
		m_playerThree.m_playerShape.setFillColor(sf::Color::Red);
		m_playerThree.m_playerShape.setPosition(randX3, 800);
	}

	//Check if the player is the chase player
	m_playerOne.checkForChasePlayer();
	m_playerTwo.checkForChasePlayer();
	m_playerThree.checkForChasePlayer();
}

void Game::checkForCollisions()
{
	
	//Collision check between player one and everyone else - also setting the timers
	if (m_client->chasePlayerNumber == 1)
	{
		//Check Player one and player Two
		if (m_playerOne.m_playerShape.getGlobalBounds().intersects(m_playerTwo.m_playerShape.getGlobalBounds()))
		{
			std::cout << "Chaser Red and Player Blue are colliding" << std::endl;
			if (m_playerTwo.m_isPlayerAlive)
			{
				m_SurvivalTime[1].setString("Player Blue has survived for: " + std::to_string(survivalClock.getElapsedTime().asSeconds()));
				m_playerTwo.m_isPlayerAlive = false;
			}
		}
		//Check player one and Player Three
		else if (m_playerOne.m_playerShape.getGlobalBounds().intersects(m_playerThree.m_playerShape.getGlobalBounds()))
		{
			std::cout << "Chaser Red and Player Magenta are colliding" << std::endl;
			if (m_playerThree.m_isPlayerAlive)
			{
				m_SurvivalTime[2].setString("Player Magenta has survived for: " + std::to_string(survivalClock.getElapsedTime().asSeconds()));
				m_playerThree.m_isPlayerAlive = false;
			}
		}
	}
	//Collision check between player Two and everyone else - also setting the timers
	else if (m_client->chasePlayerNumber == 2)
	{
		//Check Player 2 and player 1
		if (m_playerTwo.m_playerShape.getGlobalBounds().intersects(m_playerOne.m_playerShape.getGlobalBounds()))
		{
			std::cout << "Chaser Red and Player Green are colliding" << std::endl;
			if (m_playerOne.m_isPlayerAlive)
			{
				m_SurvivalTime[0].setString("Player Green has survived for: " + std::to_string(survivalClock.getElapsedTime().asSeconds()));
				m_playerOne.m_isPlayerAlive = false;
			}
		}
		//Check player 2 and player 3
		else if (m_playerTwo.m_playerShape.getGlobalBounds().intersects(m_playerThree.m_playerShape.getGlobalBounds()))
		{
			std::cout << "Chaser Red and Player Magenta are colliding" << std::endl;
			if (m_playerThree.m_isPlayerAlive)
			{
				m_SurvivalTime[2].setString("Player Magenta has survived for: " + std::to_string(survivalClock.getElapsedTime().asSeconds()));
				m_playerThree.m_isPlayerAlive = false;
			}
		}
	}
	//Collision check between player Three and everyone else - also setting the timers
	else if (m_client->chasePlayerNumber == 3)
	{
		//Check player 3 and player 1
		if (m_playerThree.m_playerShape.getGlobalBounds().intersects(m_playerOne.m_playerShape.getGlobalBounds()))
		{
			std::cout << "Chaser Red and Player Green are colliding" << std::endl;
			if (m_playerOne.m_isPlayerAlive)
			{
				m_SurvivalTime[0].setString("Player Green has survived for: " + std::to_string(survivalClock.getElapsedTime().asSeconds()));
				m_playerOne.m_isPlayerAlive = false;
			}
		}
		//Check player 3 and player 2
		else if (m_playerThree.m_playerShape.getGlobalBounds().intersects(m_playerTwo.m_playerShape.getGlobalBounds()))
		{
			if (m_playerTwo.m_isPlayerAlive)
			{
				std::cout << "Chaser Red and Player Blue are colliding" << std::endl;
				m_SurvivalTime[1].setString("Player Blue has survived for: " + std::to_string(survivalClock.getElapsedTime().asSeconds()));
				m_playerTwo.m_isPlayerAlive = false;
			}
		}
	}

}
