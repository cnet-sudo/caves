#pragma once
#include<iostream>
#include"AssetManager.h"
#include "Masha.h"
#include "Bear.h"

class GameEngine
{
public:
	// �����������
	GameEngine();
	// ����� ������� �������� �����
	void run();

private:

	// �������� ��������
	AssetManager manager; 
	// ���� � �������
	Bear m_bear;
	Masha m_masha;
	// ������ ������ � �������
	const int TILE_SIZE = 50;
	// ������ ������� ������ ���������
	const int VERTS_IN_QUAD = 4;
	// ���� ��������� ������ ���� - ����������
	// �� ������� �������� ������������ �����
	const int GRAVITY = 300;
	// ������� ����
	sf::RenderWindow m_Window;
	// ������������� ������� �����������
	sf::View m_MainView; // ������ �����
	sf::View m_LeftView; // ����� ������ ������
	sf::View m_RightView; // ������ ������ ������
	// �������� ����
	sf::View m_BGMainView;
	sf::View m_BGLeftView;
	sf::View m_BGRightView;
	sf::View m_HudView;
	// ������� � �������� ��� ����
	sf::Sprite m_BackgroundSprite;
	sf::Texture m_BackgroundTexture;
	// ��� ������� ������� ��� ���
	bool m_Playing = false;
	// ��� �� ������� � ������
	bool m_Character1 = true;
	// ������ � ������������� �����
	bool m_SplitScreen = false;
	// ���������� ����� �� ������� ������
	float m_TimeRemaining = 10;
	sf::Time m_GameTimeTotal;
	// ���� �� �������� ������
	bool m_NewLevelRequired = true;
	// ������
	sf::Image m_icon;
	// ����� ��������� ������� 
	void input();
	// ����� ���������� ����������, ������� � ������� 
	void update(float dtAsSeconds);
	// ����� ��������� �������� � ����������� ����
	void draw();
};

