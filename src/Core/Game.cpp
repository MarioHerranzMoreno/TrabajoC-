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
	if (timer < 300) 
	{
		canShoot = false;
		timer += deltaMilliseconds;
	}
	else if (timer >= 300) 
	{
		canShoot = true;
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
			//TODO las putas comprobaciones y llamar al clic
			if(event.mouseButton.button == sf::Mouse::Left)
			onClick(*m_window);
			timer = 0;
			canShoot = false;
		}
	}
	std::cout << timer << std::endl;
	// Update scene here
	m_world->update(deltaMilliseconds);
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