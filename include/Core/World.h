#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>
#include <Gameplay/Projectile.h>
#include <Gameplay/Cultist.h>

class Enemy;

namespace sf
{
	class RenderWindow;
}

namespace tmx
{
	class Map;
}

class MapLayer;

class World
{
	public:

		~World();

		bool load();


		void update(uint32_t deltaMilliseconds, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);

		void onClick(sf::Vector2f mPos);
		void onClickS(sf::Vector2f mPos);
		void spawnEnemy();


		float enemyRate = 800;
		float spawnRate;
		float difficultyCounter;

		bool gameOver = false;


		float points = 0;
		sf::Font p_font;
		sf::Text p_text;

		sf::Text gameOverText;

	private:

		Enemy* m_enemy{ nullptr };

		tmx::Map* m_map{ nullptr };
		MapLayer* m_layerZero{ nullptr };
		MapLayer* m_layerOne{ nullptr };
		MapLayer* m_layerTwo{ nullptr };
		std::vector<Cultist> m_c;
};