#include "GameEngine.h"

void GameEngine::input()
{
	sf::Event event;

	while (window->pollEvent(event))  
	{
		// Обработка события нажатия на клавишу Esc
		if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed)) 	window->close(); 
	}
}

void GameEngine::update(sf::Time const& deltaTime)
{

}

void GameEngine::draw()
{
	// Очистка графического окна
	window->clear();
	// Отрисовка фона в графическом окне
	window->draw(background);
	// Вывод объектов в графическом окне
	window->display();
}

GameEngine::GameEngine()
{
	// Получение ссылки на текстуру для прямоугольника 
	background.setFillColor(sf::Color::Green);
	if (!icon.loadFromFile("game.png")) exit(3); 
	window->setIcon(128, 128, icon.getPixelsPtr());

}

void GameEngine::run()
{
	// Объявление переменной часы
	sf::Clock clock;
	// Цикл работает пока окно открыто
	while (window->isOpen())
	{
		// Текущее время присваиваем переменной времени dt
		sf::Time dt = clock.restart();

		input();
		update(dt);
		draw();
	}
}
