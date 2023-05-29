#include "GameEngine.h"

GameEngine::GameEngine()
{
	// �������� ���������� ������
	sf::Vector2f resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	m_Window.create(sf::VideoMode(resolution.x, resolution.y), L"������",sf::Style::Fullscreen);
	// ���������������� ������������� �����
	m_MainView.setSize(resolution);
	m_HudView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// ���������������� ������������� � �����������	�������
	m_LeftView.setViewport(sf::FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_RightView.setViewport(sf::FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
	m_BGLeftView.setViewport(sf::FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_BGRightView.setViewport(sf::FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
	m_BackgroundTexture = AssetManager::GetTexture("graphics/background1.jpg");
	// ������ ������ � ���������
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	
	if (!m_icon.loadFromFile("game.png")) exit(3); 
	m_Window.setIcon(128, 128, m_icon.getPixelsPtr());

}
void GameEngine::input()
{
	sf::Event event;

	while (m_Window.pollEvent(event)) {
		
		if (event.type == sf::Event::KeyPressed) {
			// ��������� ������ ������
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

				m_Window.close();
			}
			// ��������� ������, ������������ ����
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

				m_Playing = true;
			}
			// ������������ ����� ����� � �����
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

				m_Character1 = !m_Character1;
			}
			// ������������ ����� ������ � �����������
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {

				m_SplitScreen = !m_SplitScreen;
			}

		}
		
	}
		// ��������� �����, ������������ ��� �������
		if (m_bear.handleInput())
		{
			// ������������� ���� ������
		}
		// ��������� �����, ������������ ��� ����
		if (m_masha.handleInput())
		{
			// ������������� ���� ������
		}
		
}
void GameEngine::update(float dtAsSeconds)
{
	
	if (m_NewLevelRequired)	{

		m_bear.spawn(sf::Vector2f(0, 0), GRAVITY);
		m_masha.spawn(sf::Vector2f(100, 0), GRAVITY);
		// ���������, ��� ����� ���������� ������ ���� ���
		m_TimeRemaining = 10;
		m_NewLevelRequired = false;
	}
	// ������ ����
	if (m_Playing)	{

		// ���������� ������� ����������
		m_bear.update(dtAsSeconds);
		m_masha.update(dtAsSeconds);
		// �������� ������ �������, ����� ����� ����
		m_TimeRemaining -= dtAsSeconds;
		// ����������� ������� �����
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}
	}// ����� ����

	// ����������  ��� ��� ���������������� ���������
	if (m_SplitScreen)
	{
		m_LeftView.setCenter(m_bear.getCenter());
		m_RightView.setCenter(m_masha.getCenter());
	}
	else
	{
		// ������������ ���� ����� ������ ��������������� ���������
		if (m_Character1)
		{
			m_MainView.setCenter(m_bear.getCenter());
		}
		else
		{
			m_MainView.setCenter(m_masha.getCenter());
		}
	}
}

void GameEngine::draw()
{
	//������� ��������� ����
	m_Window.clear(sf::Color::White);
	if (!m_SplitScreen)
	{
		// ������������� �� ������� ���
		m_Window.setView(m_BGMainView);
		//������ ���
		m_Window.draw(m_BackgroundSprite);
		// ������������� �� m_MainView
		m_Window.setView(m_MainView);

		// ������ ����������
		m_Window.draw(m_bear.getSprite());
		m_Window.draw(m_masha.getSprite());
	}
	else
	{
		// ����� ������������ ������ �������
       // ������� ������ ������� ������ ����
        // ������������� �� ������� ���
		m_Window.setView(m_BGLeftView);
		// ������ ���
		m_Window.draw(m_BackgroundSprite);
		// ������������� �� m_LeftView
		m_Window.setView(m_LeftView);
		// ������ ����������
		m_Window.draw(m_masha.getSprite());
		m_Window.draw(m_bear.getSprite());
	
		// ������ ������ ������� ����
		// ������������� �� ������� ���
		m_Window.setView(m_BGRightView);
		// ������ ���
		m_Window.draw(m_BackgroundSprite);
		// ������������� ��  m_RightView
		m_Window.setView(m_RightView);

		// ������ ����������
		m_Window.draw(m_bear.getSprite());
		m_Window.draw(m_masha.getSprite());
	}
	// ������ HUD
	// ������������� ��  m_HudView
	m_Window.setView(m_HudView);
	// �������� ���, ��� �� ������ ��� ����������
	m_Window.display();
}



void GameEngine::run()
{
	// ���������� ���������� ����
	sf::Clock clock;
	// ���� �������� ���� ���� �������
	while (m_Window.isOpen())
	{
		// ������� ����� ����������� ���������� ������� dt
		sf::Time dt = clock.restart();
		m_GameTimeTotal += dt;
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}
