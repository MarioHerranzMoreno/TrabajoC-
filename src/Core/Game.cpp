#include <cassert>
#include <Core/Game.h>
#include <Core/World.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>


bool Game::init(GameCreateInfo& createInfo)
{
	assert(m_window == nullptr && m_world == nullptr && "Game is already initialized, we are about to leak memory");

	m_window = new sf::RenderWindow({ createInfo.screenWidth, createInfo.screenHeight }, createInfo.gameTitle);
	m_window->setFramerateLimit(createInfo.frameRateLimit);
	m_world = new World();
	const bool loadOk = m_world->load();

	return loadOk;
}

Game::~Game()
{
	// To-Do: make sure m_world is unloaded()

	delete m_world;
	delete m_window;
}

bool Game::isRunning() const 
{ 
	return m_window->isOpen(); 
}

void Game::update(uint32_t deltaMilliseconds)
{
	//Disp1
	if (timer1 < timelimit1) 
	{
		canShoot = false;
		timer1 += deltaMilliseconds;
	}
	else if (timer1 >= timelimit1)
	{
		canShoot = true;
	}
	//Disp2
	if (timer2 < timelimit2)
	{
		canShoot2 = false;
		timer2 += deltaMilliseconds;
	}
	else if (timer2 >= timelimit2)
	{
		canShoot2 = true;
	}


	// Check if user closed the window
	for (auto event = sf::Event(); m_window->pollEvent(event);)
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}

		if (event.type == sf::Event::MouseButtonPressed && canShoot == true)
		{
			if (event.mouseButton.button == sf::Mouse::Left) 
			{
			onClick(*m_window);
			timer1 = 0;
			canShoot = false;
			}

			if (event.mouseButton.button == sf::Mouse::Right && canShoot2 == true)
			{
				onClickS(*m_window);
				timer2 = 0;
				canShoot2 = false;
			}
		}
	}
	m_world->update(deltaMilliseconds);
}


void Game::onClickS(sf::RenderWindow& window) 
{
	//Calculo de ratón
	sf::Vector2f mouseWorldP = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	m_world->onClickS(mouseWorldP);
}

void Game::onClick(sf::RenderWindow &window) 
{
	//Calculo de ratón
	sf::Vector2f mouseWorldP = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	m_world->onClick(mouseWorldP);
}

void Game::render()
{
	m_window->clear();

	m_world->render(*m_window);

	m_window->display();
}