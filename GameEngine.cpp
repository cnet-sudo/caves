#include "GameEngine.h"

GameEngine::GameEngine()
{
	// получаем разрешение экрана
	sf::Vector2f resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	m_Window.create(sf::VideoMode(resolution.x, resolution.y), L"Пещеры",sf::Style::Fullscreen);
	// Инициализировать полноэкранный режим
	m_MainView.setSize(1920,1080);
	m_HudView.reset(sf::FloatRect(0, 0, 1920, 1080));
	// Инициализировать представления с разделенным	экраном
	m_LeftView.setViewport(sf::FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_RightView.setViewport(sf::FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
	m_BGLeftView.setViewport(sf::FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_BGRightView.setViewport(sf::FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
	m_BackgroundTexture = AssetManager::GetTexture("graphics/background1.jpg");
	// Свяжем спрайт с текстурой
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	
	if (!m_icon.loadFromFile("game.png")) exit(3); 
	m_Window.setIcon(128, 128, m_icon.getPixelsPtr());

	// Загружаем текстуру для фонового массива вершин
	m_TextureTiles = AssetManager::GetTexture("graphics/levels.png");

}
void GameEngine::input()
{
	sf::Event event;

	while (m_Window.pollEvent(event)) {
		
		if (event.type == sf::Event::KeyPressed) {
			// Обработка выхода игрока
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

				m_Window.close();
			}
			// Обработка игрока, запускающего игру
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

				m_Playing = true;
			}
			// Переключение между Машей и Мишей
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

				m_Character1 = !m_Character1;
			}
			// Переключение между полным и разделенным
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {

				m_SplitScreen = !m_SplitScreen;
			}

		}
		
	}
		// Обработка ввода, характерного для медведя
		if (m_bear.handleInput())
		{
			// Воспроизвести звук прыжка
		}
		// Обработка ввода, характерного для маши
		if (m_masha.handleInput())
		{
			// Воспроизвести звук прыжка
		}
		
}
void GameEngine::update(float dtAsSeconds)
{
	
	if (m_NewLevelRequired)	{

		// Загружаем уровень
		loadLevel();
	}
	// начало игры
	if (m_Playing)	{

		// обновление свойств персонажей
		m_bear.update(dtAsSeconds);
		m_masha.update(dtAsSeconds);
		// Обнаружение столкновений и проверка, достигли ли персонажи целей
		// Вторая часть условия if выполняется 
		// только тогда, когда	Медведь касается домашней плитки

		if (detectCollisions(m_bear) && detectCollisions(m_masha))
		{
			// Требуется новый уровень
			m_NewLevelRequired = true;
			// Воспроизвести звук 
		}
		else
		{
			// Запустить обнаружение столкновений
			detectCollisions(m_masha);
		}

		// персонажи пригают друг другу на голову
		if (m_masha.getFeet().intersects(m_bear.getHead()))
		{
			m_masha.stopFalling(m_bear.getHead().top);
		}
		else if (m_bear.getFeet().intersects(m_masha.getHead()))
		{
			m_bear.stopFalling(m_masha.getHead().top);
		}

		// Обратный отсчет времени, когда игрок ушел
		//m_TimeRemaining -= dtAsSeconds;
		// Закончилось игровое время
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}
	}// конец игры

	// Установить  вид для соответствующего персонажа
	if (m_SplitScreen)
	{
		m_LeftView.setCenter(m_bear.getCenter());
		m_RightView.setCenter(m_masha.getCenter());
	}
	else
	{
		// Центрировать весь экран вокруг соответсвующего персонажа
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
	//очищаем последний кадр
	m_Window.clear(sf::Color::White);
	if (!m_SplitScreen)
	{
		// Переключиться на фоновый вид
		m_Window.setView(m_BGMainView);
		//Рисуем фон
		m_Window.draw(m_BackgroundSprite);
		// Переключиться на m_MainView
		m_Window.setView(m_MainView);
		// Рисуем уровень
		m_Window.draw(m_VALevel, &m_TextureTiles);
		// Рисуем персонажей
		m_Window.draw(m_bear.getSprite());
		m_Window.draw(m_masha.getSprite());
	}
	else
	{
		// Режим разделенного экрана активен
       // Сначала рисуем сторону экрана Маши
        // Переключиться на фоновый вид
		m_Window.setView(m_BGLeftView);
		// Рисуем фон
		m_Window.draw(m_BackgroundSprite);
		// Переключиться на m_LeftView
		m_Window.setView(m_LeftView);
		// Рисуем уровень
		m_Window.draw(m_VALevel, &m_TextureTiles);
		// Рисуем персонажей
		m_Window.draw(m_masha.getSprite());
		m_Window.draw(m_bear.getSprite());
	
		// Теперь рисуем сторону Миши
		// Переключиться на фоновый вид
		m_Window.setView(m_BGRightView);
		// Рисуем фон
		m_Window.draw(m_BackgroundSprite);
		// Переключиться на  m_RightView
		m_Window.setView(m_RightView);
		// Рисуем уровень
		m_Window.draw(m_VALevel, &m_TextureTiles);
		// Рисуем персонажей
		m_Window.draw(m_bear.getSprite());
		m_Window.draw(m_masha.getSprite());
	}
	// Рисуем HUD
	// Переключиться на  m_HudView
	m_Window.setView(m_HudView);
	// Показать все, что мы только что нарисовали
	m_Window.display();
}



void GameEngine::run()
{
	// Объявление переменной часы
	sf::Clock clock;
	// Цикл работает пока окно открыто
	while (m_Window.isOpen())
	{
		// Текущее время присваиваем переменной времени dt
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
	// Удаляем ранее выделенную память
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;
	// Загружаем следующий массив 2d с картой для уровня 
	// И снова заполняем массив вершин
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);
	// Сколько длится этот новый лимит времени
	m_TimeRemaining = m_LM.getTimeLimit();
	// Создаем персонажей
	m_bear.spawn(m_LM.getStartPosition(), GRAVITY);
	m_masha.spawn(m_LM.getStartPosition(), GRAVITY);
	// Убедитесь, что этот код больше не запускается
	m_NewLevelRequired = false;
}

bool GameEngine::detectCollisions(Character& character)
{
	bool reachedGoal = false;
	// Зона обнаружения персонажа
	sf::FloatRect detectionZone = character.getPosition();
	// Сделать FloatRect для проверки каждого блока
	sf::FloatRect block;
	block.width = TILE_SIZE;
	block.height = TILE_SIZE;
	// Строим зону вокруг медеведя для обнаружения столкновений
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	// Медведь довольно высокий, поэтому проверьте несколько плиток по вертикали
	int endY = (int)(detectionZone.top / TILE_SIZE) + 5;
	// Убедитесь, что мы не проверяем позиции ниже нуля 
	// Или выше конца массива
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;
	// Персонаж выпал за пределы карты? 
	sf::FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE,
								m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		// возрождаем персонажа
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}
	// Перебираем все локальные блоки
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Инициализировать начальную позицию текущего блока
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;
			// Персонаж сгорел или утонул? 
			// Используйте голову,	так как это позволит ему немного утонуть
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					// Какой звук должен воспроизводиться ?
					if (m_ArrayLevel[y][x] == 2) // Огонь
					{
						// Воспроизвести звук
					}
					else // Вода
					{
						// Воспроизвести звук
					}
				}
			}
			// Персонаж сталкивается с обычным блоком
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
			// Здесь будет больше обнаружения столкновений, 
			// когда появятся эффекты частиц
			if (m_ArrayLevel[y][x] == 4)
			{
				// Персонаж достиг цели
				reachedGoal = true;
			}
		}
	}

	return reachedGoal;
}