#pragma once
#include<iostream>
#include"AssetManager.h"

class GameEngine
{
public:
	// Конструктор
	GameEngine();
	// Метод запуска игрового цикла
	void run();
private:
	AssetManager manager; // Менеджер ресурсов
	// Умный указатель на графическое окно 
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720),L"Моя игра", sf::Style::Default);
	// Игровой фон в виде прямоугольника
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(1280, 720));
	sf::Image icon;
	// Метод обработки событий 
	void input();
	// Метод обновления переменных, свойств и методов 
	void update(sf::Time const& deltaTime);
	// Метод отрисовки объектов в графическом окне
	void draw();
};

