#include "Bear.h"

Bear::Bear() {

	// ������ �������� �� ��������
	m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/bear.png"));
	m_JumpDuration = .45;
}

// ����������� �������
bool Bear::handleInput() {
	m_JustJumped = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// ������ ������, ���� �� ��� �� ������
        // �� ������ ���� ������ �� ����� (�� ������) 
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}
	return m_JustJumped;
}