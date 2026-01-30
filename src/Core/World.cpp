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

	// To-Do, read ALL from file, this is just a quick example to understand that here is where entities are created but consider grouping/managing actors in a smarter way
	sf::Texture* zombieTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/mage.png");
	Zombie::ZombieDescriptor zombieDescriptor;
	zombieDescriptor.texture = zombieTexture;
	zombieDescriptor.position = { 940.f, 540.f };
	zombieDescriptor.speed = { 400.f * millisecondsToSeconds, .0f }; // 400 units per second, or 0.4 units per millisecond, using the latter so it's in alignment with delta time
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


	return initOk;
}

void World::update(uint32_t deltaMilliseconds)
{
	m_layerZero->update(sf::milliseconds(deltaMilliseconds));

	if (spawnRate > 800) 
	{
		spawnRate = 0;
		spawnEnemy();
	}
	spawnRate += deltaMilliseconds;

	Zombie* zombie = dynamic_cast<Zombie*>(m_enemy);
	//std::vector<Projectile> p = zombie->getProjectiles();
	/*for (Cultist& c : m_c)
	{
		c.update(deltaMilliseconds);
		for (Projectile& proj : p) 
		{
			if (proj.getBounds().intersects(c.getBounds())) 
			{
				p.end();
				m_c.end();
			}
		}
	}*/

	for (auto deadCult = m_c.begin(); deadCult != m_c.end(); )
	{
		deadCult->update(deltaMilliseconds);
		bool cultistDead = false;

		auto& projectiles = zombie->getProjectiles();

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
}

void World::onClick(sf::Vector2f mPos) 
{
	m_enemy->onClick(mPos);
}

void World::spawnEnemy()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.1, 0.2);
	std::uniform_real_distribution<double> dist2(0.8, 0.9);
	std::uniform_int_distribution<int> side(0, 1);


	Cultist cult;
	Cultist::CultistDescriptor desc;
	//desc.target = m_position;
	desc.target = { 940.f, 540.f };
	desc.speed = { 100.f, 100.f };
	desc.position = {
		static_cast<float>((side(mt) ? dist(mt) : dist2(mt))) * 1920,
		static_cast<float>((side(mt) ? dist(mt) : dist2(mt))) * 1080,
	};
	cult.init(desc);
	m_c.push_back(cult);
}