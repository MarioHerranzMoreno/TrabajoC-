#include <Core/AssetManager.h>
#include <Core/World.h>
#include <Gameplay/Zombie.h>
#include <Gameplay/Cultist.h>
#include <Render/SFMLOrthogonalLayer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmxlite/Map.hpp>
#include <random>

World::~World()
{
	delete m_enemy;
	delete m_layerZero;
	delete m_layerOne;
	delete m_layerTwo;
	delete m_map;
}

bool World::load()
{
	constexpr float millisecondsToSeconds = 1 / 1000.f;

	sf::Texture* zombieTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/mage.png");
	Zombie::ZombieDescriptor zombieDescriptor;
	zombieDescriptor.texture = zombieTexture;
	zombieDescriptor.position = { 940.f, 540.f };
	zombieDescriptor.speed = { 100.f * millisecondsToSeconds, 100.0f * millisecondsToSeconds }; // 400 units per second, or 0.4 units per millisecond, using the latter so it's in alignment with delta time
	zombieDescriptor.tileWidth = 16.f;
	zombieDescriptor.tileHeight = 16.f;
	Zombie* zombie = new Zombie();
	const bool initOk = zombie->init(zombieDescriptor);

	m_enemy = zombie;
	m_enemy->setPosition(zombieDescriptor.position);

	// To-Do, Load level: this should have its own class
	m_map = new tmx::Map();
	m_map->load("../Data/Levels/MapMaybe.tmx");

	m_layerZero = new MapLayer(*m_map, 0);
	m_layerOne = new MapLayer(*m_map, 1);
	m_layerTwo = new MapLayer(*m_map, 2);


	if (!p_font.loadFromFile("../Data/Fonts/Utext.otf"))
		return false;

	p_text.setFont(p_font);
	p_text.setCharacterSize(24);
	p_text.setFillColor(sf::Color::White);
	p_text.setPosition(10.f, 10.f);

	gameOverText.setFont(p_font);
	gameOverText.setCharacterSize(58);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition(660.f, 650.f);


	return initOk;
}

void World::update(uint32_t deltaMilliseconds)
{
	if (gameOver)
	{
		gameOverText.setString("Your score:" + std::to_string(static_cast<int>(points)));
		return;
	}

	m_layerZero->update(sf::milliseconds(deltaMilliseconds));
	const float deltaSeconds = deltaMilliseconds / 10;

	//Points
	points += deltaSeconds;
	p_text.setString("Points: " + std::to_string(static_cast<int>(points)));


	if (spawnRate > enemyRate) 
	{
		spawnRate = 0;
		spawnEnemy();
	}
	if (difficultyCounter >= 14000 && enemyRate > 200)
	{
		enemyRate -= 100;
		difficultyCounter = 0;
	}
	if(difficultyCounter < 14000)
		difficultyCounter += deltaMilliseconds;

	spawnRate += deltaMilliseconds;


	Zombie* zombie = dynamic_cast<Zombie*>(m_enemy);
	

	for (auto deadCult = m_c.begin(); deadCult != m_c.end(); )
	{
		deadCult->update(deltaMilliseconds);
		bool cultistDead = false;

		auto& projectiles = zombie->getProjectiles();
		auto& projectiles2 = zombie->getProjectiles2();

		for (auto p = projectiles.begin(); p != projectiles.end(); )
		{
			if (p->getBounds().intersects(deadCult->getBounds()))
			{
				p = projectiles.erase(p);
				cultistDead = true;
				break;
			}
			else
			{
				++p;
			}

			if (!cultistDead)
			{
				for (auto p2 = projectiles2.begin(); p2 != projectiles2.end(); ++p2)
				{
					if (p2->getBounds().intersects(deadCult->getBounds()))
					{
						cultistDead = true;
						break;
					}
				}
			}

			if (deadCult->getBounds().intersects(zombie->getBounds()))
			{
				gameOver = true;
				return;
			}
		}
		if (cultistDead)
		{
		deadCult = m_c.erase(deadCult);
		}
		else
		++deadCult;


	}



	m_enemy->update(deltaMilliseconds);

}

void World::render(sf::RenderWindow& window)
{
	window.draw(*m_layerZero);
	window.draw(*m_layerOne);
	window.draw(*m_layerTwo);
	m_enemy->render(window);

	for (Cultist& c : m_c)
	{
		c.render(window);
	}

	window.draw(p_text);

	if(gameOver)
	window.draw(gameOverText);
}


void World::onClickS(sf::Vector2f mPos)
{
	m_enemy->onClickS(mPos);
}

void World::onClick(sf::Vector2f mPos) 
{
	m_enemy->onClick(mPos);
}

void World::spawnEnemy()
{
	std::random_device rd;
	std::mt19937 mt(rd());


	std::uniform_real_distribution<float> leftX(0.1f, 0.35f);
	std::uniform_real_distribution<float> rightX(0.7f, 0.95f);
	std::uniform_real_distribution<float> anyX(0.01f, 0.99f);
	std::uniform_real_distribution<float> anyY(0.01f, 0.99f);
	std::uniform_int_distribution<int> side(0, 3);

	Cultist cult;
	Cultist::CultistDescriptor desc;
	desc.target = m_enemy->getPosition();
	desc.speed = { 80.f, 80.f };

	int spawnSide = side(mt);

	float x, y;

	switch (spawnSide)
	{
	case 0:
		x = leftX(mt) * 1920.f;
		y = anyY(mt) * 1080.f;
		break;

	case 1:
		x = rightX(mt) * 1920.f;
		y = anyY(mt) * 1080.f;
		break;

	case 2:
		x = anyX(mt) * 1920.f;
		y = 0.f;
		break;

	case 3:
		x = anyX(mt) * 1920.f;
		y = 1080.f;
		break;
	}

	desc.position = { x, y };
	cult.init(desc);
	m_c.push_back(cult);
}