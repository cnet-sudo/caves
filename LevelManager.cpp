#include "LevelManager.h"
#include <sstream>
#include <fstream>

void LevelManager::nextLevel(std::vector<std::vector<int>> & matrix, sf::VertexArray& rVaLevel, int level) {
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;
	
	// загрузка уровня
	std::string levelToLoad;
	switch (level)
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
	// Проходим по файлу и сохраняем 
	// все значения в массиве 2d
	std::string row;
	int y = 0;
	while (inputFile >> row)
	{
		std::vector<int> v;
		for (int x = 0; x < row.length(); x++) {
						
			std::string s(1, row[x]);
			v.push_back(std::stoi(s));
		}
		matrix.push_back(v);
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
			int verticalOffset = matrix[y][x] * TILE_SIZE;
			rVaLevel[currentVertex + 0].texCoords =	sf::Vector2f(0+ verticalOffset, 0 );
			rVaLevel[currentVertex + 1].texCoords =	sf::Vector2f(0 + verticalOffset,TILE_SIZE);
			rVaLevel[currentVertex + 2].texCoords =	sf::Vector2f(TILE_SIZE + verticalOffset,TILE_SIZE);
			rVaLevel[currentVertex + 3].texCoords =	sf::Vector2f(TILE_SIZE + verticalOffset,0);
			// Готовая позиция для следующих четырех вершин
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	
} 

sf::Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}


float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;
}

sf::Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}