#pragma once

#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Sprite.hpp>


class Enemy : public GameObject
{
	public:

		struct EnemyDescriptor
		{
			sf::Vector2f position;
			sf::Texture* texture{ nullptr };
			float tileWidth{ .0f };
			float tileHeight{ .0f };
		};

		~Enemy() override = default;

		bool init(const EnemyDescriptor& enemyDescriptor);

		void update(float deltaMilliseconds) override;
		void render(sf::RenderWindow& window) override;

		virtual void onClick(sf::Vector2f mPos) = 0;

	protected:

		sf::Sprite m_sprite;
		sf::Transform m_rotation;
		float m_tileWidth{ .0f };
		float m_tileHeight{ .0f };
};