#include <Gameplay/ProjectileS.h>
#include <SFML/Window/Keyboard.hpp>
#include <Gameplay/Enemy.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

//Projectile::Projectile() = default;


bool ProjectileS::init(const ProjectileSDescriptor& projectileSDescriptor)
{
	m_position = projectileSDescriptor.position;

	
	//p_sprite.setScale(1, 1);

	shape.setOrigin(-8.f,-8.f);
	shape.setFillColor(sf::Color(250, 00, 200));
	shape.setRadius(pRadius);
	shape.setPosition(m_position);

	return true;
}

void ProjectileS::update(float deltaMilliseconds)
{
	const float deltaSeconds = deltaMilliseconds / 100;


	
	
		if (cd > cdLimit)
			m_active = false;

		if (cd < cdLimit)
		cd += deltaSeconds;

		std::cout << cd << std::endl;

		shape.setPosition(m_position);

}

void ProjectileS::render(sf::RenderWindow& window) 
{
	window.draw(shape);
}

sf::FloatRect ProjectileS::getBounds() const
{
	return shape.getGlobalBounds();
}