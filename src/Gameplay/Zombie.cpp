#include <Gameplay/Zombie.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window.hpp>
#include <Core/Game.h>
#include <SFML/Graphics.hpp>
#include <Gameplay/GameObject.h>
#include <iostream>

bool Zombie::init(const ZombieDescriptor& zombieDescriptor)
{
	m_speed = zombieDescriptor.speed;
	m_sprite.setScale(2, 2);
	m_position = zombieDescriptor.position;
	return Enemy::init(zombieDescriptor);
}

void Zombie::onClick(sf::Vector2f mPos)
{
	//direccion de mirar
	sf::Vector2f dir = mPos - m_position;

	shoot(dir);
}

void Zombie::shoot(sf::Vector2f mouse)
{
	//Crear proyectil
	//Hacerle mirar a X posicion
	Projectile p;
	Projectile::ProjectileDescriptor desc;
	desc.target = mouse;
	desc.speed = { 400.f, 200.f };
	desc.position = m_position;
	p.init(desc);
	m_p.push_back(p);
}


void Zombie::update(float deltaMilliseconds)
{
	for (Projectile& p : m_p) 
	{
		p.update(deltaMilliseconds);
	}



	Enemy::update(deltaMilliseconds);
}


void Zombie::render(sf::RenderWindow& window) 
{
	Enemy::render(window);
	
	for (Projectile& p : m_p)
	{
		p.render(window);
	}
	
}
	