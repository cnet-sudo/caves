#pragma once
#include<iostream>
#include<string>
#include "Masha.h"
#include "Bear.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

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
	// ������ ������ ������
	ParticleSystem m_PS;
	// ���� � �������
	Bear m_bear;
	Masha m_masha;
	// ����� ��� ���������� ����� ��������
	LevelManager m_LM;
	// 2d ������� ����� ������
	std::vector<std::vector<int>> m_matrix;
	// ����� ��� ���������� �������
	SoundManager m_SM;
	// ���������
	HUD m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;
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
	// �������� ������ ��� ����
	sf::Shader m_RippleShader;

	// ��� ������� ������� ��� ���
	bool m_Playing = false;
	// ��� �� ������� � ������
	bool m_Character1 = true;
	// ������ � ������������� �����
	bool m_SplitScreen = false;
	// ���������� ����� �� ������� ������
	float m_TimeRemaining = 10.0f;
	sf::Time m_GameTimeTotal;
	// ���� �� �������� ������
	bool m_NewLevelRequired = true;
	// ������ ������ ��� ������ ������
	sf::VertexArray m_VALevel;
	// �������� ������ ������ Texture
	sf::Texture m_TextureTiles;
	// ������
	sf::Image m_icon;
	// ����� ��������� ������� 
	void input();
	// ����� ���������� ����������, ������� � ������� 
	void update(float dtAsSeconds);
	// ����� ��������� �������� � ����������� ����
	void draw();

	// ��������� ����� �������
	void loadLevel();

	bool detectCollisions(Character& character);

	// ������� ������ ���� ��� ��������������� ����� 
	void populateEmitters(std::vector <sf::Vector2f>& vSoundEmitters);
	
	// ������ Vector2f ��� �������������� ��������� ���� vector
	std::vector <sf::Vector2f> m_FireEmitters;
};

