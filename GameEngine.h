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
	// Конструктор
	GameEngine();
	// Метод запуска игрового цикла
	void run();

private:

	// Менеджер ресурсов
	AssetManager manager; 
	// Создаём ситему частиц
	ParticleSystem m_PS;
	// Маша и Медведь
	Bear m_bear;
	Masha m_masha;
	// Класс для управления всеми уровнями
	LevelManager m_LM;
	// 2d матрица карты уровня
	std::vector<std::vector<int>> m_matrix;
	// Класс для управления музыкой
	SoundManager m_SM;
	// Интерфейс
	HUD m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;
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
	// Объявить шейдер для фона
	sf::Shader m_RippleShader;

	// Идёт игровой процесс или нет
	bool m_Playing = false;
	// Кто из игроков в фокусе
	bool m_Character1 = true;
	// Запуск в полноэкранный режим
	bool m_SplitScreen = false;
	// Оставшееся время на текущем уровне
	float m_TimeRemaining = 10.0f;
	sf::Time m_GameTimeTotal;
	// Надо ли начинать заново
	bool m_NewLevelRequired = true;
	// Массив вершин для тайлов уровня
	sf::VertexArray m_VALevel;
	// Текстура тайлов уровня Texture
	sf::Texture m_TextureTiles;
	// иконка
	sf::Image m_icon;
	// Метод обработки событий 
	void input();
	// Метод обновления переменных, свойств и методов 
	void update(float dtAsSeconds);
	// Метод отрисовки объектов в графическом окне
	void draw();

	// Загружаем новый уровень
	void loadLevel();

	bool detectCollisions(Character& character);

	// Создаем вектор мест для воспроизведения звука 
	void populateEmitters(std::vector <sf::Vector2f>& vSoundEmitters);
	
	// Вектор Vector2f для местоположения источника огня vector
	std::vector <sf::Vector2f> m_FireEmitters;
};

