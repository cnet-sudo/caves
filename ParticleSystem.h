#pragma once
#include "Particle.h"
#include <random>

class ParticleSystem: public sf::Drawable
{
	std::vector<Particle> m_Particles;
	sf::VertexArray m_Vertices;
	float m_Duration;
	bool m_IsRunning = false;

public:

	virtual void draw(sf::RenderTarget& target,	sf::RenderStates states) const;
	void init(int count);
	void emitParticles(sf::Vector2f position);
	void update(float elapsed);
	bool running();
};

