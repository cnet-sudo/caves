#include "GameEngine.h"

void GameEngine::input()
{
	sf::Event event;

	while (window->pollEvent(event))  
	{
		// ��������� ������� ������� �� ������� Esc
		if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed)) 	window->close(); 
	}
}

void GameEngine::update(sf::Time const& deltaTime)
{

}

void GameEngine::draw()
{
	// ������� ������������ ����
	window->clear();
	// ��������� ���� � ����������� ����
	window->draw(background);
	// ����� �������� � ����������� ����
	window->display();
}

GameEngine::GameEngine()
{
	// ��������� ������ �� �������� ��� �������������� 
	background.setFillColor(sf::Color::Green);
	if (!icon.loadFromFile("game.png")) exit(3); 
	window->setIcon(128, 128, icon.getPixelsPtr());

}

void GameEngine::run()
{
	// ���������� ���������� ����
	sf::Clock clock;
	// ���� �������� ���� ���� �������
	while (window->isOpen())
	{
		// ������� ����� ����������� ���������� ������� dt
		sf::Time dt = clock.restart();

		input();
		update(dt);
		draw();
	}
}
