#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <Gameplay/Enemy.h>
#include <SFML/Graphics.hpp>
#include <Gameplay/GameObject.h>


class Projectile : public GameObject
{
	public:

		struct ProjectileDescriptor 
		{
			sf::Vector2f speed{ .0f, .0f };
			sf::Vector2f target{ .0f, .0f };
			sf::Vector2f position{ .0f, .0f };
		};

		bool init(const ProjectileDescriptor& projectileDescriptor);
		

		void update(float deltaMilliseconds) override;
		void render(sf::RenderWindow& window) override;

		sf::FloatRect getBounds() const;

		//Projectile();

	private:

		sf::Vector2f p_target{.0f,.0f};
		sf::Vector2f p_direction{ .0f, .0f };
		sf::Vector2f p_speed{ .0f, .0f };
		sf::Sprite p_sprite;
		float p_tileWidth{ .0f };
		float p_tileHeight{ .0f };
		sf::CircleShape shape;
};