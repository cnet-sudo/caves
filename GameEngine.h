#pragma once
#include<iostream>
#include"AssetManager.h"
#include "Masha.h"
#include "Bear.h"

class GameEngine
{
public:
	// Конструктор
	GameEngine();
	// Метод запуска игрового цикла
	void run();

private:

	// Менеджер ресурсов
	AssetManager manager; 
	// Маша и Медведь
	Bear m_bear;
	Masha m_masha;
	// размер плиток в спрайте
	const int TILE_SIZE = 50;
	// четыре вершины четырёх угольника
	const int VERTS_IN_QUAD = 4;
	// сила толкающая объект вниз - гравитация
	// на сколько пикселей переместится игрок
	const int GRAVITY = 300;
	// игровое окно
	sf::RenderWindow m_Window;
	// представления экранов отображения
	sf::View m_MainView; // полный экран
	sf::View m_LeftView; // левый раздел экрана
	sf::View m_RightView; // правый раздел экрана
	// варианты фона
	sf::View m_BGMainView;
	sf::View m_BGLeftView;
	sf::View m_BGRightView;
	sf::View m_HudView;
	// Спрайты и текстуры для фона
	sf::Sprite m_BackgroundSprite;
	sf::Texture m_BackgroundTexture;
	// Идёт игровой процесс или нет
	bool m_Playing = false;
	// Кто из игроков в фокусе
	bool m_Character1 = true;
	// Запуск в полноэкранный режим
	bool m_SplitScreen = false;
	// Оставшееся время на текущем уровне
	float m_TimeRemaining = 10;
	sf::Time m_GameTimeTotal;
	// Надо ли начинать заново
	bool m_NewLevelRequired = true;
	// иконка
	sf::Image m_icon;
	// Метод обработки событий 
	void input();
	// Метод обновления переменных, свойств и методов 
	void update(float dtAsSeconds);
	// Метод отрисовки объектов в графическом окне
	void draw();
};

