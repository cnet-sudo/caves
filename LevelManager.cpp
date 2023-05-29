#include "LevelManager.h"
#include <sstream>
#include <fstream>

int** LevelManager::nextLevel(sf::VertexArray& rVaLevel) {
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;
	// следующий уровень
	m_CurrentLevel++;
	if (m_CurrentLevel > NUM_LEVELS)
	{
		m_CurrentLevel = 1;
		m_TimeModifier -= .1f;
	}
	// загрузка уровня
	std::string levelToLoad;
	switch (m_CurrentLevel)
	{
	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		m_BaseTimeLimit = 30.0f;
		break;
	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;
	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;
	case 4:
		levelToLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;
	}// Конец переключателя

	std::ifstream inputFile(levelToLoad);
	std::string s;
	// Подсчитываем количество строк в файле
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}
	// Сохраняем длину строк
	m_LevelSize.x = s.length();
	// Вернуться к началу файла
	inputFile.clear();
	inputFile.seekg(0, std::ios::beg);
	// Подготавливаем 2D-массив для хранения значений int из файла в int**
	int** arrayLevel = new int* [m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Добавляем новый массив в каждый элемент
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	// Проходим по файлу и сохраняем 
	// все значения в массиве 2d
	std::string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < row.length(); x++) {
			const char val = row[x];
			arrayLevel[y][x] = atoi(&val);
		}
		y++;
	}
	// Закрыть файл
	inputFile.close();
	// Какой тип примитива мы используем?
	rVaLevel.setPrimitiveType(sf::Quads);
	// Установить размер массива вершин
	rVaLevel.resize(m_LevelSize.x *	m_LevelSize.y * VERTS_IN_QUAD);
	// Начать с начала массива вершин
	int currentVertex = 0;
	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			// Позиционируем каждую вершину в текущем четырехугольнике
			rVaLevel[currentVertex + 0].position =sf::Vector2f(x * TILE_SIZE,y * TILE_SIZE);
			rVaLevel[currentVertex + 1].position =sf::Vector2f((x * TILE_SIZE) + TILE_SIZE,y * TILE_SIZE);
			rVaLevel[currentVertex + 2].position =sf::Vector2f((x * TILE_SIZE) + TILE_SIZE,(y * TILE_SIZE) + TILE_SIZE);
			rVaLevel[currentVertex + 3].position =sf::Vector2f((x * TILE_SIZE),(y * TILE_SIZE) + TILE_SIZE);
			// Какой тайл из листа спрайтов мы должны использовать
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;
			rVaLevel[currentVertex + 0].texCoords =	sf::Vector2f(0+ verticalOffset, 0 );
			rVaLevel[currentVertex + 1].texCoords =	sf::Vector2f(0 + verticalOffset,TILE_SIZE);
			rVaLevel[currentVertex + 2].texCoords =	sf::Vector2f(TILE_SIZE + verticalOffset,TILE_SIZE);
			rVaLevel[currentVertex + 3].texCoords =	sf::Vector2f(TILE_SIZE + verticalOffset,0);
			// Готовая позиция для следующих четырех вершин
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	return arrayLevel;
} 

sf::Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}

int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}

float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;
}

sf::Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}