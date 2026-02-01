#pragma once

#include <cstdint>
#include <string>

namespace sf
{
	class RenderWindow;
}

class World;

class Game
{
	public:

		struct GameCreateInfo
		{
			std::string gameTitle;
			uint32_t screenWidth;
			uint32_t screenHeight;
			uint32_t frameRateLimit;
		};

		~Game();

		bool init(GameCreateInfo& createInfo);

		bool isRunning() const;


		void update(uint32_t deltaMilliseconds);
		void render();

		void onClick(sf::RenderWindow &window);
		void onClickS(sf::RenderWindow &window);

		bool canShoot = true;
		bool canShoot2 = true;
		float timer1 = 20;
		float timer2 = 600;

		float timelimit1 = 300;
		float timelimit2 = 2000;


	private:

		sf::RenderWindow* m_window{ nullptr };
		World* m_world{ nullptr };
};