#include <Gameplay/Projectile.h>
#include <SFML/Window/Keyboard.hpp>
#include <Gameplay/Enemy.h>
#include <Gameplay/Cultist.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <random>

//Projectile::Projectile() = default;


bool Cultist::init(const CultistDescriptor& cultistDescriptor)
{
	m_position = cultistDescriptor.position;
	p_speed = cultistDescriptor.speed;
	p_target = cultistDescriptor.target;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(20.f, 30.f);
	std::uniform_real_distribution<double> dist2(20.f, 30.f);

	
	//p_sprite.setScale(1, 1);

	shape.setFillColor(sf::Color(150, 50, 250));
	shape.setSize(sf::Vector2f(dist(mt), dist2(mt)));
	shape.setPosition(m_position);

	return true;
}

void Cultist::update(float deltaMilliseconds)
{
	const float deltaSeconds = deltaMilliseconds / 1000;
	sf::Vector2f direction = p_target -m_position;

	const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length > 0.001f)
	{
		direction /= length;

		p_direction = direction;
	}
	//p_direction = m_position;

	m_position.x += (p_direction.x * p_speed.x * deltaSeconds);
	m_position.y += (p_direction.y * p_speed.y * deltaSeconds);
	shape.setPosition(m_position);

	//std::cout << "=========== M.Pos ===========" << std::endl;
	//std::cout << "X: " << m_position.x << "Y: " << m_position.y << std::endl;
	//std::cout << "=========== P.DIr ===========" << std::endl;
	//std::cout << "X: " << p_direction.x << "Y: " << p_direction.y << std::endl;
	std::cout << "=========== Target ===========" << std::endl;
	std::cout << "X: " << p_target.x << "Y: " << p_target.y << std::endl;
	//std::cout << "=========== Speed ===========" << std::endl;
	//std::cout << "X: " << p_speed.x << "Y: " << p_speed.y << std::endl;

	//TODO descubrir donde definir la forma (tamaño textura tal) del proyectil, y descubrir como crear
	//los proyectiles con el clic
}

void Cultist::render(sf::RenderWindow& window) 
{
	window.draw(shape);
}

sf::FloatRect Cultist::getBounds() const
{
	return shape.getGlobalBounds();
}