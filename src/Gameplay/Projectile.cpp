#include <Gameplay/Projectile.h>
#include <SFML/Window/Keyboard.hpp>
#include <Gameplay/Enemy.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

//Projectile::Projectile() = default;


bool Projectile::init(const ProjectileDescriptor&  projectileDescriptor)
{
	m_position = projectileDescriptor.position;
	p_speed = projectileDescriptor.speed;
	p_target = projectileDescriptor.target;

	

	shape.setOrigin(-8.f,-8.f);
	shape.setFillColor(sf::Color(250, 100, 00));
	shape.setRadius(15.f);
	shape.setPosition(m_position);

	return true;
}

void Projectile::update(float deltaMilliseconds)
{
	const float deltaSeconds = deltaMilliseconds / 1000;
	sf::Vector2f direction = p_target;
	const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length > 0.001f)
	{
		direction /= length;

		p_direction = direction;
	}

	m_position.x += (p_direction.x * p_speed.x * deltaSeconds);
	m_position.y += (p_direction.y * p_speed.y * deltaSeconds);
	shape.setPosition(m_position);

	/*std::cout << "=========== M.Pos ===========" << std::endl;
	std::cout << "X: " << m_position.x << "Y: " << m_position.y << std::endl;
	std::cout << "=========== P.DIr ===========" << std::endl;
	std::cout << "X: " << p_direction.x << "Y: " << p_direction.y << std::endl;
	std::cout << "=========== Target ===========" << std::endl;
	std::cout << "X: " << p_target.x << "Y: " << p_target.y << std::endl;
	std::cout << "=========== Speed ===========" << std::endl;
	std::cout << "X: " << p_speed.x << "Y: " << p_speed.y << std::endl;*/

}

void Projectile::render(sf::RenderWindow& window) 
{
	window.draw(shape);
}

sf::FloatRect Projectile::getBounds() const
{
	return shape.getGlobalBounds();
}