#pragma once
#include"AssetManager.h"

class Character {

	protected:
		//  sprite персонажа
		sf::Sprite m_Sprite;
		// величина времени прыжка
		// чем больше значение, тем дальше и выше сможет прыгнуть персонаж
		float m_JumpDuration;
		// персонаж сейчас прыгает или падает bool
		// ограничения прыжка в воздухе
		bool m_IsJumping;
		bool m_IsFalling;
		// в каком направлении движется персонаж в данный момент
		bool m_LeftPressed;
		bool m_RightPressed;
		// как долго  длился прыжок
		float m_TimeThisJump;
		// игрок только что совершил прыжок
		bool m_JustJumped = false;

	private:
		// гравитация
		float m_Gravity;
		// насколько быстр персонаж
		float m_Speed = 400;
		// где находится игрок
		sf::Vector2f m_Position;
		// где находятся различные части тела персонажей
		sf::FloatRect m_Feet;
		sf::FloatRect m_Head;
		sf::FloatRect m_Right;
		sf::FloatRect m_Left;
		// текстура
		sf::Texture m_Texture;
	public:
		void spawn(sf::Vector2f startPosition, float gravity);
		// чисто виртуальная функция
		bool virtual handleInput() = 0;
		// Этот класс теперь абстрактный и не может быть создан
		// Где находится игрок
		sf::FloatRect getPosition();
		// Прямоугольник, представляющий положение 
		// различных частей спрайта
		sf::FloatRect getFeet();
		sf::FloatRect getHead();
		sf::FloatRect getRight();
		sf::FloatRect getLeft();
		// возвращаем копию спрайта
		sf::Sprite getSprite();
		// Заставить персонажа стоять прочно
		void stopFalling(float position);
		void stopRight(float position);
		void stopLeft(float position);
		void stopJump();
		// Где находится центр персонажа 
		sf::Vector2f getCenter();
		// Мы будем вызывать эту функцию один раз в каждом кадре
		void update(float elapsedTime);
};	

