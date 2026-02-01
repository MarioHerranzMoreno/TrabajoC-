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

void Zombie::onClickS(sf::Vector2f mPos)
{
	//Position
	sf::Vector2f appear = { mPos.x - 48.f, mPos.y - 48.f };;


	shootS(appear);
}

void Zombie::shoot(sf::Vector2f mouse)
{
	//Crear proyectil
	Projectile p;
	Projectile::ProjectileDescriptor desc;
	desc.target = mouse;
	desc.speed = { 200.f, 200.f };
	desc.position = m_position;
	p.init(desc);
	m_p.push_back(p);
}


void Zombie::shootS(sf::Vector2f mouse)
{
	//Crear proyectil
	ProjectileS pS;
	ProjectileS::ProjectileSDescriptor desc;
	desc.position = mouse;
	pS.init(desc);
	m_pS.push_back(pS);
}


void Zombie::update(float deltaMilliseconds)
{
	//Move
	m_direction = { 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_direction.x = -1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_direction.x = 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_direction.y = -1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_direction.y = 1.0f;
	}

	m_position.x += (m_direction.x * m_speed.x * deltaMilliseconds);
	m_position.y += (m_direction.y * m_speed.y * deltaMilliseconds);





	//Update of projectiles
	for (Projectile& p : m_p) 
	{
		p.update(deltaMilliseconds);
	}
	for (ProjectileS& pS : m_pS)
	{
		pS.update(deltaMilliseconds);
	}


	//SP lifetime
	for (auto pS = m_pS.begin(); pS != m_pS.end();)
	{
		pS->update(deltaMilliseconds);

		if (!pS->isActive())
			pS = m_pS.erase(pS);
		else
			++pS;
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
	for (ProjectileS& pS : m_pS)
	{
		pS.render(window);
	}

	
	
}


std::vector<Projectile>& Zombie::getProjectiles()
{
	return m_p;
}


std::vector<ProjectileS>& Zombie::getProjectiles2()
{
	return m_pS;
}
	

sf::FloatRect Zombie::getBounds() const
{
	return m_sprite.getGlobalBounds();
}