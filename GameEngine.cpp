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

	// ��������� �������� ��� �������� ������� ������
	m_TextureTiles = AssetManager::GetTexture("graphics/levels.png");

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

		// ��������� �������
		loadLevel();
	}
	// ������ ����
	if (m_Playing)	{

		// ���������� ������� ����������
		m_bear.update(dtAsSeconds);
		m_masha.update(dtAsSeconds);
		// ����������� ������������ � ��������, �������� �� ��������� �����
		// ������ ����� ������� if ����������� 
		// ������ �����, �����	������� �������� �������� ������

		if (detectCollisions(m_bear) && detectCollisions(m_masha))
		{
			// ��������� ����� �������
			m_NewLevelRequired = true;
			// ������������� ���� 
		}
		else
		{
			// ��������� ����������� ������������
			detectCollisions(m_masha);
		}

		// ��������� ������� ���� ����� �� ������
		if (m_masha.getFeet().intersects(m_bear.getHead()))
		{
			m_masha.stopFalling(m_bear.getHead().top);
		}
		else if (m_bear.getFeet().intersects(m_masha.getHead()))
		{
			m_bear.stopFalling(m_masha.getHead().top);
		}

		// �������� ������ �������, ����� ����� ����
		//m_TimeRemaining -= dtAsSeconds;
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
		// ������ �������
		m_Window.draw(m_VALevel, &m_TextureTiles);
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
		// ������ �������
		m_Window.draw(m_VALevel, &m_TextureTiles);
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
		// ������ �������
		m_Window.draw(m_VALevel, &m_TextureTiles);
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

void GameEngine::loadLevel()
{
	m_Playing = false;
	// ������� ����� ���������� ������
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;
	// ��������� ��������� ������ 2d � ������ ��� ������ 
	// � ����� ��������� ������ ������
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);
	// ������� ������ ���� ����� ����� �������
	m_TimeRemaining = m_LM.getTimeLimit();
	// ������� ����������
	m_bear.spawn(m_LM.getStartPosition(), GRAVITY);
	m_masha.spawn(m_LM.getStartPosition(), GRAVITY);
	// ���������, ��� ���� ��� ������ �� �����������
	m_NewLevelRequired = false;
}

bool GameEngine::detectCollisions(Character& character)
{
	bool reachedGoal = false;
	// ���� ����������� ���������
	sf::FloatRect detectionZone = character.getPosition();
	// ������� FloatRect ��� �������� ������� �����
	sf::FloatRect block;
	block.width = TILE_SIZE;
	block.height = TILE_SIZE;
	// ������ ���� ������ �������� ��� ����������� ������������
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	// ������� �������� �������, ������� ��������� ��������� ������ �� ���������
	int endY = (int)(detectionZone.top / TILE_SIZE) + 5;
	// ���������, ��� �� �� ��������� ������� ���� ���� 
	// ��� ���� ����� �������
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;
	// �������� ����� �� ������� �����? 
	sf::FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE,
								m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		// ���������� ���������
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}
	// ���������� ��� ��������� �����
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// ���������������� ��������� ������� �������� �����
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;
			// �������� ������ ��� ������? 
			// ����������� ������,	��� ��� ��� �������� ��� ������� �������
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					// ����� ���� ������ ���������������� ?
					if (m_ArrayLevel[y][x] == 2) // �����
					{
						// ������������� ����
					}
					else // ����
					{
						// ������������� ����
					}
				}
			}
			// �������� ������������ � ������� ������
			if (m_ArrayLevel[y][x] == 1)
			{
				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}
				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
			}
			// ����� ����� ������ ����������� ������������, 
			// ����� �������� ������� ������
			if (m_ArrayLevel[y][x] == 4)
			{
				// �������� ������ ����
				reachedGoal = true;
			}
		}
	}

	return reachedGoal;
}