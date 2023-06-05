#pragma once
#include"AssetManager.h"
#include <cmath>
class HUD
{
		sf::Font m_Font;
		sf::Text m_StartText;
		sf::Text m_TimeText;
		sf::Text m_LevelText;
		sf::Vector2u m_resolution;

	public:

		HUD();

		sf::Text getMessage();
		sf::Text getLevel();
		sf::Text getTime();
		void setLevel(int level);
		void setTime(float time);
	
};

