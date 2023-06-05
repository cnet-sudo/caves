#include "Character.h"

void Character::spawn( sf::Vector2f startPosition, float gravity) {

	// Ставим игрока в начальную точку
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;
	// Инициализируем гравитацию
	m_Gravity = gravity;
	// Переместить спрайт в позицию
	m_Sprite.setPosition(m_Position);
}

void Character::update(float elapsedTime) {

	if (m_RightPressed)	{

		m_Position.x += m_Speed * elapsedTime;
	}
	if (m_LeftPressed) {

		m_Position.x -= m_Speed * elapsedTime;
	}
	// Обработка перехода
	if (m_IsJumping) {

		// Обновить, как долго продолжается прыжок
		m_TimeThisJump += elapsedTime;
		// Прыжок идет вверх
		if (m_TimeThisJump < m_JumpDuration) {
			// Двигаемся вверх с удвоенной силой тяжести 
			m_Position.y -= m_Gravity * 2 * elapsedTime;
		}
		else {
			m_IsJumping = false;
			m_IsFalling = true;
		}
	}
	// Применение гравитации
	if (m_IsFalling) {

		m_Position.y += m_Gravity * elapsedTime;
	}
	// Обновить прямоугольник для всех частей
	sf::FloatRect r = getPosition();
	// Ноги
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;
	// Голова
	m_Head.left = r.left+50;
	m_Head.top = r.top + (r.height * .1);
	m_Head.width = r.width-100;
	m_Head.height = 1;
	// Правый 
	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;
	// Левый
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .5;
	m_Left.width = 1;
	m_Left.height = r.height * .3;
	// Переместить спрайт 
	m_Sprite.setPosition(m_Position);
}

sf::FloatRect Character::getPosition() {

	return m_Sprite.getGlobalBounds();
}

sf::Vector2f Character::getCenter() {

	return sf::Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

sf::FloatRect Character::getFeet() {

	return m_Feet;
}

sf::FloatRect Character::getHead() {

	return m_Head;
}

sf::FloatRect Character::getLeft() {

	return m_Left;
}

int Character::getIdentifier()
{
	return m_identifier;
}

sf::FloatRect Character::getRight() {

	return m_Right;
}

sf::Sprite Character::getSprite() {

	return m_Sprite;
}

void Character::stopFalling(float position) {

	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

void Character::stopRight(float position) {

	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Character::stopLeft(float position) {

	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Character::stopJump() {

	// Досрочно прекратить
	m_IsJumping = false;
	m_IsFalling = true;
}