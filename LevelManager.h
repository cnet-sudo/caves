#pragma once
#include"AssetManager.h"

class LevelManager
{	
	// ���������� ������ �� ��������� � �����������
	sf::Vector2i m_LevelSize;
	// ���������� ��������� ����������
	sf::Vector2f m_StartPosition;
	// ����������� ������� ��� ���������� ����������� ������
	float m_TimeModifier = 1;
	// ������������������ �������� �������
	float m_BaseTimeLimit = 0;
	// ����� ����� ��������� �� ������� 1
	const int NUM_LEVELS = 4;

public:
	// ������ ������
	const int TILE_SIZE = 50;
	// ���������� ������ ��� ������� ������
	const int VERTS_IN_QUAD = 4;
	float getTimeLimit();
	sf::Vector2f getStartPosition();
	// ���������� ������
	void nextLevel(std::vector<std::vector<int>>& matrix,sf::VertexArray& rVaLevel,int level);
	sf::Vector2i getLevelSize();
	
};

