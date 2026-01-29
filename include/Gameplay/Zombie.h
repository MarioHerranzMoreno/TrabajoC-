#pragma once
#include <Gameplay/Projectile.h>
#include <Gameplay/Enemy.h>


class Zombie : public Enemy
{
	public:

		struct ZombieDescriptor : EnemyDescriptor
		{
			sf::Vector2f speed{ .0f, .0f };
		};

		bool init(const ZombieDescriptor& enemyDescriptor);

		void update(float deltaMilliseconds);


		void shoot(sf::Vector2f mouse);
		void onClick(sf::Vector2f mPos) override;

		void render(sf::RenderWindow& window) override;


	private:

		//Lo guardamos aqui porque esta plantilla es una mierda
		std::vector<Projectile> m_p;
		sf::Vector2f m_rotation{ .0f, .0f };
		sf::Vector2f m_direction{ .0f, .0f };
		sf::Vector2f m_speed{ .0f, .0f };
};