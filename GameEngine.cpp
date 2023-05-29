#include "GameEngine.h"

GameEngine::GameEngine()
{
	// получаем разрешение экрана
	sf::Vector2f resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	m_Window.create(sf::VideoMode(resolution.x, resolution.y), L"Пещеры",sf::Style::Fullscreen);
	// Инициализировать полноэкранный режим
	m_MainView.setSize(resolution);
	m_HudView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
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

		m_bear.spawn(sf::Vector2f(0, 0), GRAVITY);
		m_masha.spawn(sf::Vector2f(100, 0), GRAVITY);
		// Убедитесь, что спавн вызывается только один раз
		m_TimeRemaining = 10;
		m_NewLevelRequired = false;
	}
	// начало игры
	if (m_Playing)	{

		// обновление свойств персонажей
		m_bear.update(dtAsSeconds);
		m_masha.update(dtAsSeconds);
		// Обратный отсчет времени, когда игрок ушел
		m_TimeRemaining -= dtAsSeconds;
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
