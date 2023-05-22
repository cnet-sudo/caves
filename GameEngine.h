#pragma once
#include<iostream>
#include"AssetManager.h"

class GameEngine
{
public:
	// �����������
	GameEngine();
	// ����� ������� �������� �����
	void run();
private:
	AssetManager manager; // �������� ��������
	// ����� ��������� �� ����������� ���� 
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720),L"��� ����", sf::Style::Default);
	// ������� ��� � ���� ��������������
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(1280, 720));
	sf::Image icon;
	// ����� ��������� ������� 
	void input();
	// ����� ���������� ����������, ������� � ������� 
	void update(sf::Time const& deltaTime);
	// ����� ��������� �������� � ����������� ����
	void draw();
};

