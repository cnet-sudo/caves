#pragma once
#include"AssetManager.h"

class LevelManager
{	
	// количество плиток по вертикали и горизонтали
	sf::Vector2i m_LevelSize;
	// координаты появления персонажей
	sf::Vector2f m_StartPosition;
	// модификатор времени для усложнения прохождения уровня
	float m_TimeModifier = 1;
	// немодифицированный интервал времени
	float m_BaseTimeLimit = 0;
	// текущий уровень
	int m_CurrentLevel = 0;
	// когда нужно вернуться на уровень 1
	const int NUM_LEVELS = 4;

public:
	// размер плиток
	const int TILE_SIZE = 50;
	// количество вершин для массива вершин
	const int VERTS_IN_QUAD = 4;
	float getTimeLimit();
	sf::Vector2f getStartPosition();
	// построение уровня
	int** nextLevel(sf::VertexArray& rVaLevel);
	sf::Vector2i getLevelSize();
	int getCurrentLevel();
};

