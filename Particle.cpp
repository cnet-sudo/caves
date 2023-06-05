#include "Particle.h"

Particle::Particle(sf::Vector2f direction)
{
	// Определяем направление
	m_Velocity.x = direction.x;
	m_Velocity.y = direction.y;
}
void Particle::update(float dtAsSeconds)
{
	// Переместить частицу
	m_Position += m_Velocity * dtAsSeconds;
}
void Particle::setPosition(sf::Vector2f position)
{
	m_Position = position;
}

sf::Vector2f Particle::getPosition()
{
	return m_Position;
}