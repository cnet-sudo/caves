#include "HUD.h"
HUD::HUD()
{
	m_resolution.x = sf::VideoMode::getDesktopMode().width;
	m_resolution.y = sf::VideoMode::getDesktopMode().height;
	m_Font.loadFromFile("fonts/Disket-Mono-Bold.ttf");
	// пауза
	m_StartText.setFont(m_Font);
	m_StartText.setCharacterSize(50);
	m_StartText.setFillColor(sf::Color::White);
	m_StartText.setString(L"Нажмите Enter, когда будете готовы!");
	sf::FloatRect textRect = m_StartText.getLocalBounds();
	m_StartText.setOrigin(textRect.left +textRect.width / 2.0f, textRect.top +textRect.height / 2.0f);
	m_StartText.setPosition(m_resolution.x / 2.0f, m_resolution.y / 2.0f);
	// Время
	m_TimeText.setFont(m_Font);
	m_TimeText.setCharacterSize(50);
	m_TimeText.setFillColor(sf::Color::White);
	m_TimeText.setString("------");
	// Уровень
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(50);
	m_LevelText.setFillColor(sf::Color::White);
	m_LevelText.setPosition(25, 0);
	m_LevelText.setString("1");
}

sf::Text HUD::getMessage()
{
	return m_StartText;
}
sf::Text HUD::getLevel()
{
	return m_LevelText;
}
sf::Text HUD::getTime()
{
	return m_TimeText;
}

void HUD::setLevel(int level) {

	sf::String str = L"Уровень:";
	sf::String str1 = std::to_string(level);
	m_LevelText.setString(str+str1);
}

void HUD::setTime(float time)
{
	std::string str = std::to_string(time);
	str.erase(4,4);
	m_TimeText.setString(str);
	m_TimeText.setPosition(m_resolution.x - m_TimeText.getGlobalBounds().width, 0);
}