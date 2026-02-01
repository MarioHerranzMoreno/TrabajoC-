#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <Gameplay/Enemy.h>
#include <SFML/Graphics.hpp>
#include <Gameplay/GameObject.h>


class ProjectileS : public GameObject
{
	public:

		struct ProjectileSDescriptor
		{
			sf::Vector2f position{ .0f, .0f };
		};

		bool init(const ProjectileSDescriptor& projectileSDescriptor);
		

		void update(float deltaMilliseconds) override;
		void render(sf::RenderWindow& window) override;

		bool isActive() const { return m_active; };

		sf::FloatRect getBounds() const;

		float cd = 0;
		float cdLimit = 11;

		float pRadius = 50.f;


	private:

		bool m_active = true;
		sf::Sprite p_sprite;
		float p_tileWidth{ .0f };
		float p_tileHeight{ .0f };
		sf::CircleShape shape;
};