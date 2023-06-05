#include "ParticleSystem.h"

void ParticleSystem::init(int numParticles)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib_angle(0, 360);
	std::uniform_real_distribution<> distrib_speed(600, 1200);
	
	m_Vertices.setPrimitiveType(sf::Points);
	m_Vertices.resize(numParticles);
	// Создаем частицы
	for (int i = 0; i < numParticles; i++)
	{
		float angle = distrib_angle(gen) * 3.14f / 180.f;
		float speed = distrib_speed(gen);
		sf::Vector2f direction;
		direction = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
		m_Particles.push_back(Particle(direction));
	}
}

void ParticleSystem::update(float dt)
{
	m_Duration -= dt;
	std::vector<Particle>::iterator i;
	int currentVertex = 0;
	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		// Переместить частицу
		(*i).update(dt);
		// Обновить массив вершин
		m_Vertices[currentVertex++].position = i->getPosition();
	}
	if (m_Duration < 0)
	{
		m_IsRunning = false;
	}
}

void ParticleSystem::emitParticles(sf::Vector2f startPosition)
{
	m_IsRunning = true;
	m_Duration = 2;
	int currentVertex = 0;
	for (auto it = m_Particles.begin();
		it != m_Particles.end();
		it++)
	{
		m_Vertices[currentVertex++].color = sf::Color::Yellow;
		it->setPosition(startPosition);
	}
}

void ParticleSystem::draw(sf::RenderTarget& target,	sf::RenderStates states) const
{
	target.draw(m_Vertices, states);
}

bool ParticleSystem::running()
{
	return m_IsRunning;
}